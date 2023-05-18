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