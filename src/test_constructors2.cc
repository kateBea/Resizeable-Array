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

    kt::vector<double> vec1{ 3.2, 4.5, .5, 8.4 };
    kt::vector<double> vec2(vec1.begin(), vec1.end());
    kt::vector<double> vec3(vec2.begin(), 2);
    kt::vector<double> vec4(vec1);

    std::cout << "Elements vec1: ";
    show(vec1.begin(), vec1.end());

    std::cout << std::endl;

    std::cout << "Elements vec2: ";
    show(vec2.begin(), vec2.end());

    std::cout << std::endl;

    std::cout << "Elements vec3: ";
    show(vec3.begin(), vec3.end());

    std::cout << std::endl;

    std::cout << "Elements vec4: ";
    show(vec4.begin(), vec4.end());



    return 0;
}