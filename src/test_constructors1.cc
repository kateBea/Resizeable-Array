#include <iostream>
#include <iomanip>

#include <vector.hh>


template<typename InputIt>
auto show(InputIt first, InputIt last) {
    while (first != last)
        std::cout << *(first++) << ' ';
}

int main(int, char**) {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(4);

    kt::vector<double> vec1{};

    std::cout << "vec1.size(): " << vec1.size() << std::endl;
    std::cout << "vec1.capacity(): " << vec1.capacity() << std::endl;

    kt::vector<double> vec2(5);

    std::cout << "vec2.size(): " << vec2.size() << std::endl;
    std::cout << "vec2.capacity(): " << vec2.capacity() << std::endl;

    kt::vector<double> vec3{ 3.0, 4.5, 6.7, 3.2, 8.9, 6.9 };

    std::cout << "vec3.size(): " << vec3.size() << std::endl;
    std::cout << "vec3.capacity(): " << vec3.capacity() << std::endl;
    show(vec3.begin(), vec3.end());

    return 0;
}