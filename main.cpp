#include <iostream>
#include <iterator>
#include <vector>

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

#define N 200

int main()
{
    std::vector<int> arr(N);

    for (int i = N; i >= 0; i--)
    arr[i] = i;
    merge_sort(arr.begin(), arr.end());
    for (int i = 0; i < N; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    
}