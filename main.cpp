#include <iostream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <string>
#include "kaizen.h"

int BLOCK_SIZE = 12288;
int N = 20000000;

template<typename Iterator>
void merge(Iterator first, Iterator mid, Iterator last) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    std::vector<value_type> tmp(first, last);
    Iterator left = tmp.begin();
    Iterator right = tmp.begin() + (mid - first);
    Iterator end = tmp.end();
    Iterator current = first;
    
    while (left < right && right < end) {
        if (*left <= *right) {
            *current = *left++;
        } else {
            *current = *right++;
        }
        ++current;
    }
    while (left < right) {
        *current++ = *left++;
    }
    while (right < end) {
        *current++ = *right++;
    }
}

template <typename Iterator>
void merge_sort(Iterator first, Iterator last)
{
    auto distance = std::distance(first, last);
    if (distance <= 1)
    return;
    Iterator mid = first;
    std::advance(mid, distance/2);
    merge_sort(first, mid);
    merge_sort(mid, last);
    merge(first, mid, last);
}

template<typename Iterator>
void cache_aware_merge_sort(Iterator first, Iterator last) {
    auto distance = std::distance(first, last);
    if (distance <= 1)
        return;

    Iterator block_start = first;
    while (block_start != last) {
        Iterator block_end = block_start;
        auto remaining = std::distance(block_start, last);
        auto block_size = std::min(BLOCK_SIZE, static_cast<int>(remaining));
        std::advance(block_end, block_size);
        
        merge_sort(block_start, block_end);
        block_start = block_end;
    }

    for (int size = BLOCK_SIZE; size < distance; size *= 2) {
        Iterator left = first;
        while (left != last) {
            Iterator mid = left;
            auto remaining = std::distance(left, last);
            if (remaining <= size) break;

            std::advance(mid, size);
            Iterator right = mid;
            std::advance(right, std::min(size, static_cast<int>(std::distance(mid, last))));
            
            merge(left, mid, right);
            left = right;
        }
    }
}

int main(int argc, char** argv)
{
    zen::cmd_args args(argv, argc);
    if (args.is_present("--block-size"))
    {
        auto block_size = std::stoi(args.get_options("--block-size")[0]);
        if (block_size > 0)
        BLOCK_SIZE = block_size;
    }
    if (args.is_present("--n"))
    {
        auto n = std::stoi(args.get_options("--n")[0]);
        if (n > 0)
            N = n;
    }

    std::vector<int> arr(N);

    for (int i = N; i >= 0; i--)
        arr[i] = i;
    zen::timer timer;
    timer.start();
    merge_sort(arr.begin(), arr.end());
    timer.stop();
    auto merge_sort_time = timer.duration<zen::timer::msec>().count();
    timer.start();
    cache_aware_merge_sort(arr.begin(), arr.end());
    timer.stop();
    auto cache_aware_time = timer.duration<zen::timer::msec>().count();
    auto speedup = cache_aware_time ? static_cast<double>(merge_sort_time) / cache_aware_time : 0;
    if (merge_sort_time < cache_aware_time)
        speedup = merge_sort_time ? static_cast<double>(cache_aware_time) / merge_sort_time : 0;
    auto difference = cache_aware_time - merge_sort_time;
    if (merge_sort_time > cache_aware_time)
        difference = merge_sort_time - cache_aware_time;

    std::cout << "Array size: " << N << " elements" << std::endl;
    std::cout << "Block size: " << BLOCK_SIZE << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "                Merge Sort (ms)  Cache-Aware Merge Sort (ms)  Speedup (x)   Difference\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "Access Time    " << std::setw(14) << merge_sort_time << "    "
              << std::setw(20) << cache_aware_time << "       "
              << std::setw(8) << speedup << "       "
              << std::setw(8) << difference << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    return 0;
}