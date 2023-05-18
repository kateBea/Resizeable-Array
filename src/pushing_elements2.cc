#include <iostream>
#include <random>
#include <utility>
#include <vector.hh>

class Resource {
public:
    explicit Resource(int id = 0) : identifier_{ id } { std::cerr << "Constructing: " << identifier_ << '\n'; }
    Resource(Resource&& other) : identifier_{ other.identifier_ } { other.identifier_ = -1; std::cerr << "Moving: " << identifier_ << '\n'; }
    void show_value() const { std::cerr << identifier_ << '\n'; }
    ~Resource() { std::cerr << "Resource destruction... identifier: " << identifier_ << '\n'; }
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
    kt::vector<Resource> resources{};
    resources.push_back(std::move(Resource(::get_random_integer())));
    resources.push_back(std::move(Resource(::get_random_integer())));
    resources.push_back(std::move(Resource(::get_random_integer())));
    resources.push_back(std::move(Resource(::get_random_integer())));
    resources.push_back(std::move(Resource(::get_random_integer())));

    for (const auto& item : resources)
        item.show_value();

    resources.remove_n(5);

    std::cerr << "Finishing program...\n";
    return 0;
}