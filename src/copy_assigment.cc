#include <iostream>
#include <memory>
#include <random>
#include <vector.hh>

class Resource {
public:
    explicit Resource(int id = 0) : identifier_{ id } {}
    void show_value() { std::cout << identifier_ << std::endl; }
    ~Resource() { std::cout << "Objects destruction..." << std::endl; }
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
    kt::vector<std::shared_ptr<Resource>> items{};
    kt::vector<std::shared_ptr<Resource>> other_items{ std::make_shared<Resource>(11) };
    items.push_back(std::make_shared<Resource>(::get_random_integer()));
    items.push_back(std::make_shared<Resource>(::get_random_integer()));
    items.push_back(std::make_shared<Resource>(::get_random_integer()));
    items.push_back(std::make_shared<Resource>(::get_random_integer()));
    items.push_back(std::make_shared<Resource>(::get_random_integer()));
    items.push_back(std::make_shared<Resource>(::get_random_integer()));

    std::cout << "items vector contents: ";
    for (const auto& it : items)
        it->show_value();

    other_items = items;

    std::cout << "other_items vector contents: ";
    for (const auto& it : other_items)
        it->show_value();

    return 0;
}