#include <iostream>

#include <vector.hh>

int main(int, char**) {
    kt::vector<double> vec1{};

    std::cout << "vec1.size(): " << vec1.size() << std::endl;
    std::cout << "vec1.capacity(): " << vec1.capacity() << std::endl;

    kt::vector<double> vec2(5);

    std::cout << "vec2.size(): " << vec2.size() << std::endl;
    std::cout << "vec2.capacity(): " << vec2.capacity() << std::endl;

    return 0;
}