# Simple vector class
Attempt of implementation of a class to encapsulate dynamically resizeable arrays.

A dynamic resizable array is an array-like data structure that can change its size 
dynamically at runtime. It starts with a certain initial capacity and grows or 
shrinks as needed, based on the number of elements may hold.

The advantage of a dynamic array over a static array is that it allows for more 
flexibility in the size of the array, makes it easier to deal with task that require 
extra space during runtime.

This encapsulation is implemented using a pointer that owns a block of data with two integral 
values that keep track of how big is the chuc¡nk of memory held by the pointer and how
many valid elements there are.

An exmaple of a resizeable array is the **vector** class from the standard library in C++
(**std::vector<T>**) which this implementation is partially inspered on. This implementation
is aimed to support any type that is both copy assigneable and copy constructible.

Below an example of usage:

```cpp
#include <iostream>
#include <vector.hh>

int main(int, char**) {
    kt::vector<int> my_vector;

    // Adding elements to the vector
    my_vector.push_back(10);
    my_vector.push_back(20);
    my_vector.push_back(30);
    my_vector.push_back(40);

    std::cout << "First element: " << my_vector[0] << std::endl;
    std::cout << "Second element: " << my_vector[1] << std::endl;

    std::cout << "Vector contents: ";
    for (int i = 0; i < my_vector.size(); i++) {
        std::cout << my_vector[i] << " ";
    }
    
    std::cout << std::endl;
    my_vector.pop_back();
    std::cout << "Vector size: " << my_vector.size() << std::endl;

    my_vector.clear();
    std::cout << "Vector size after clearing: " << my_vector.size() << std::endl;

    return 0;
}
```
```shell
# Building and executing the example
# Clone repository
git clone --recursive repo_url
cd Resizeable-Array

# Build application
mkdir build
cd build
cmake ..
cmake --build .

# Run application
./dinArray
```
