# Cache-Aware vs. Cache-Oblivious Merge Sort  

This project compares the performance of a standard Merge Sort algorithm (cache-oblivious) with a cache-aware version designed to take advantage of CPU cache behavior.  

---

## **Introduction**  

### **Merge Sort Overview**  
Merge Sort is a classic divide-and-conquer algorithm that splits an array into two halves, sorts them recursively, and merges the sorted halves. It has a time complexity of `O(n log n)` and works efficiently even for large datasets.  

### **Cache-Oblivious vs. Cache-Aware Sorting**  

- **Cache-Oblivious Algorithms**  
  A cache-oblivious algorithm is designed without any specific knowledge of the underlying CPU cache size or structure. The algorithm relies on the natural behavior of the memory hierarchy to minimize cache misses.  
  - Merge Sort is inherently cache-oblivious because it follows a divide-and-conquer approach, which creates a hierarchical memory access pattern that is naturally cache-efficient.  

- **Cache-Aware Algorithms**  
  A cache-aware algorithm is explicitly optimized for the size of the CPU cache. It processes data in blocks that fit within the cache to minimize cache misses and maximize memory locality.  
  - The cache-aware version of Merge Sort in this project sorts data in chunks of size `BLOCK_SIZE` and merges them incrementally, aiming to reduce cache misses by improving memory access patterns.  

### **Why Cache-Aware Merge Sort May Be Slower**  
Merge Sort is already well-optimized for cache access due to its hierarchical structure. Introducing cache-awareness can increase the overhead because:  
- Extra memory allocation is required to handle data in blocks.  
- Additional logic for managing block boundaries adds complexity and processing time.  
Therefore, the cache-aware version might perform slightly worse or show minimal improvement compared to the standard merge sort.  

---

## **Example Output**  
Example output when sorting an array of size 20,000,000:  

```  
Array size: 20000000 elements  
  
----------------------------------------------------------------------------------------  
                Merge Sort (ms)  Cache-Aware Merge Sort (ms)  Speedup (x)   Difference  
----------------------------------------------------------------------------------------  
Access Time             15113                   15237           1.01            124  
----------------------------------------------------------------------------------------  
```  

In this case:  
- The cache-aware version is slightly slower because the additional memory management overhead outweighs the benefits of improved cache efficiency.  
- The speedup factor is close to 1, showing no significant advantage from the cache-aware optimization.  

---

## **How to Build and Run**  

### **1. Clone the Repository**  
```bash
git clone https://github.com/LyudmilaKostanyan/AoS-vs-SoA.git  
cd AoS-vs-SoA  
```

### **2. Build the Project**  
Use CMake to build the project:  
```bash
cmake -S . -B build  
cmake --build build  
```

### **3. Run the Program**  
Navigate to the build directory and run the executable:  
```bash
cd build  
./main.exe  
```  

---

## **Explanation of Code**  
### **Merge Sort**  
- `merge_sort` function implements the classic recursive merge sort algorithm.  
- It divides the array into two halves, sorts them recursively, and merges the results using the `merge` function.  

### **Cache-Aware Merge Sort**  
- `cache_aware_merge_sort` divides the input into fixed-size blocks (`BLOCK_SIZE = 12288`).  
- Each block is sorted individually using `merge_sort`.  
- Adjacent sorted blocks are merged iteratively in powers of two until the entire array is sorted.  

### **Performance Measurement**  
- The `zen::timer` class measures the execution time of both sorting methods.  
- The program compares execution times and calculates the speedup and difference between the two approaches.  
