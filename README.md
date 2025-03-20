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
Block size: 12288
  
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
git clone https://github.com/LyudmilaKostanyan/Cache-Aware-Merge-Sort.git  
cd Cache-Aware-Merge-Sort
```

### **2. Build the Project**  
Use CMake to build the project:  
```bash
cmake -S . -B build  
cmake --build build  
```

### **3. Run the Program**  
### **For Windows Users**  
**Example with arguments:**  
```bash
./build/main.exe --block-size 300 --n 20000
```

**Example without arguments (uses default values):**  
```bash
./build/main.exe
```

### **For Linux/macOS Users**  
If you are using **Linux** or **macOS**, the executable will be called `main` instead of `main.exe`. Run it like this:

```bash
./build/main --block-size 300 --n 20000
```

or without arguments:

```bash
./build/main
```

---

### **Explanation**  
- `--block-size`: Sets the block size used in the cache-aware merge sort.  
- `--n`: Sets the size of the array to be sorted.  

### **Default Values**  
If you don't specify the values, the program will use the following defaults:

- `BLOCK_SIZE = 12288`  
- `N = 20000000`  

#### **Why `BLOCK_SIZE = 12288`?**  
The default block size of **12288 elements** is based on the size of the L1 cache and the size of the data type being sorted:  

1. The L1 cache size on the target CPU is **48 KB** (49152 bytes).  
2. The array is composed of `int` values, which are **4 bytes** each.  
3. 48 KB ÷ 4 bytes= 12288 elements.  

By setting the block size to 12288 elements (which fits within the L1 cache), the program minimizes cache misses and improves sorting performance by ensuring that the data being processed fits entirely in the L1 cache. This increases memory locality and reduces the need to access slower levels of memory. 
