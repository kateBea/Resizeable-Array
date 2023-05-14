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



    return 0;
}