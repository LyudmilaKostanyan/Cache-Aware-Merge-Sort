#include <iostream>
#include <iterator>
#include <vector>
#include "kaizen.h"

const int BLOCK_SIZE = 12288;

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

#define N 20000000

int main()
{
    std::vector<int> arr(N);

    for (int i = N; i >= 0; i--)
        arr[i] = i;
    zen::timer timer;
    timer.start();
    merge_sort(arr.begin(), arr.end());
    timer.stop();
    std::cout << "merge_sort: " << timer.duration<zen::timer::msec>().count() << std::endl;
    timer.start();
    cache_aware_merge_sort(arr.begin(), arr.end());
    timer.stop();
    std::cout << "cache_aware_merge_sort: " << timer.duration<zen::timer::msec>().count() << std::endl;
    timer.start();
    std::sort(arr.begin(), arr.end());
    timer.stop();
    std::cout << "std::sort: " << timer.duration<zen::timer::msec>().count() << std::endl;
    return 0;
}