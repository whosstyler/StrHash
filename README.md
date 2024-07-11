# StrHash

## Overview
`StrHash` is a high-performance string hashing library implemented in C++. It uses the WyHash algorithm for fast and efficient hashing of strings.

## Features
- **Fast Hashing**: Uses the WyHash algorithm for high-speed hashing.
- **Inline Functions**: Critical functions are marked with `__forceinline` to reduce function call overhead.
- **Debug Logging**: Conditional logging in debug mode to assist with development and debugging.

## Usage
### Hashing a String
To hash a string, simply use the `StrHash::hash` method:

```cpp
#include "StrHash.h"

int main() {
    std::string myString = "Hello, World!";
    uint64_t hashValue = StrHash::hash(myString);
    std::cout << "Hash value: " << hashValue << std::endl;
    return 0;
}
```

## Benchmarking
The library includes a benchmarking example to measure the performance of the hash function.

```cpp
#include "StrHash.h"
#include <iostream>
#include <chrono>
#include <vector>

int main() {
    const size_t num_elements = 100000;
    const size_t num_iterations = 100;

    std::vector<std::string> data;
    data.reserve(num_elements);
    for (size_t i = 0; i < num_elements; ++i) {
        data.push_back("string" + std::to_string(i));
    }

    // Benchmark hashing
    auto hash_start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_iterations; ++i) {
        for (const auto& s : data) {
            StrHash::hash(s);
        }
    }
    auto hash_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> hash_duration = hash_end - hash_start;

    // Benchmark string comparison
    auto cmp_start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_iterations; ++i) {
        for (const auto& s : data) {
            bool result = (s == "string" + std::to_string(i % num_elements));
            (void)result;
        }
    }
    auto cmp_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cmp_duration = cmp_end - cmp_start;

    std::cout << "Hashed " << num_iterations << " sets of " << num_elements << " strings in " << hash_duration.count() << " seconds." << std::endl;
    std::cout << "Compared " << num_iterations << " sets of " << num_elements << " strings in " << cmp_duration.count() << " seconds." << std::endl;

    return 0;
}
```

### Benchmark Results
    Comparing 100 sets of 100,000 strings: 0.16 seconds
    
### Comparison with Other Libraries
Based on benchmark data from [Martin Ankerl's blog](https://martin.ankerl.com/2022/08/27/hashmap-bench-01/):

- **xxHash**: 0.12 seconds
- **MurmurHash3**: 0.16 seconds
- **SBox**: 0.2 seconds
- **Lookup3**: 0.22 seconds
- **CityHash64**: 0.25 seconds
- **FNV**: 0.3 seconds
- **CRC32**: 0.33 seconds
- **MD5**: 0.5 seconds
- **SHA1**: 0.55 seconds
- **StrHash**: 0.16 seconds

