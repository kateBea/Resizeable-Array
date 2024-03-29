# Simple vector class
Implementation attempt of a class that encapsulates a dynamically resizeable array.

A dynamic resizable array is an array-like data structure that can change its size 
dynamically i.e., at runtime. It starts with a certain initial capacity and grows or 
shrinks as needed, based on the number of elements it may hold.

The advantage of a dynamic array over a static array is that it allows for more 
flexibility in the size of the array, especially when it is unknown at compile time, also makes it easier to deal with tasks that require 
extra space during runtime.

This encapsulation is implemented using a pointer that owns a block of data with two integral 
values: one that keeps track of how big is the block of memory held by the pointer and another that tells how
many valid elements are in that block.

An exmaple of a resizeable array is the **vector** class from the standard library in C++
(**std::vector<T>**) which this implementation is partially inspired on. This implementation
is aimed to support any type that is both copy-assignable and copy constructible.

Below an example of usage in file [demo](src/demo.cc):

```cpp
#include <iostream>
#include <vector.hh>

int main(int, char**) {
    kt::vector<int> ints{};

    ints.push_back(10);
    ints.push_back(20);
    ints.push_back(30);
    ints.push_back(40);

    std::cout << "First element: " << ints.front() << std::endl;
    std::cout << "Last element:  " << ints.back() << std::endl;

    std::cout << "Vector contents: ";

    for (const auto& item : ints)
        std::cout << item << ' ';
    std::cout << "Vector size: " << ints.size() << std::endl;

    std::cout << "\nCalling pop_back()..." << std::endl;

    ints.pop_back();
    std::cout << "Vector size: " << ints.size() << std::endl;

    ints.clear();
    std::cout << "Vector size after clearing: " << ints.size() << std::endl;

    return 0;
}
```

# Building and running
Steps to build and run the examples. Just clone the repo and build the project with CMake, it comes with a couple of examples.
```shell
# Building and executing the example
# Clone repository
git clone repo_url
cd Resizeable-Array

# Build application
mkdir build
cd build
cmake ..
cmake --build .

# Run application
./demo
```
