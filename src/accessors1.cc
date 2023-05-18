#include <iostream>
#include <random>
#include <vector.hh>

class Resource {
public:
    explicit Resource(int id = 0) : identifier_{ id } {}
    void show_value() const { std::cout << identifier_ << std::endl; }
    ~Resource() { std::cout << "Resource destruction..." << std::endl; }
private:
    int identifier_{};
};

int get_random_integer() {
    static constexpr auto upper_bound{ 100 };
    static constexpr auto lower_bound{ 1 };
    static std::mt19937 mt{ std::random_device{}() };
    static std::uniform_int_distribution uniform_dist{ lower_bound, upper_bound };

    return uniform_dist(mt);
}

int main(int, char**) {
    kt::vector<Resource> real_numbers{};
    kt::vector<Resource> numbers1{};

    real_numbers.push_back(Resource{ ::get_random_integer() });
    real_numbers.push_back(Resource{ ::get_random_integer() });
    real_numbers.push_back(Resource{ ::get_random_integer() });
    real_numbers.push_back(Resource{ ::get_random_integer() });

    numbers1.push_back(Resource{ ::get_random_integer() });
    numbers1.push_back(Resource{ ::get_random_integer() });
    numbers1.push_back(Resource{ ::get_random_integer() });
    numbers1.push_back(Resource{ ::get_random_integer() });



    for (const auto& it : real_numbers)
        it.show_value();

    std::cout << std::endl;

    std::cout << "Front element: ";
    real_numbers.front().show_value();

    std::cout << "Back element: ";
    real_numbers.back().show_value();

    std::cout << "Popping back an element...\n";
    real_numbers.pop_back();

    std::cout << "Back element: ";
    real_numbers.back().show_value();

    std::cout << "Adding another back element...\n";
    real_numbers.push_back(Resource{ ::get_random_integer() });

    std::cout << "Back element: ";
    real_numbers.back().show_value();

    std::cout << "Contents to append: \n";
    for (const auto& it : real_numbers)
        it.show_value();

    std::cout << "Appending contents to non empty vector...\n";
    numbers1.append(real_numbers);

    for (const auto& it : numbers1)
        it.show_value();


    return 0;
}