#include "vector.h"

class Resource
{
public:
    std::size_t m_id{};

    Resource(std::size_t id = 0)
        :   m_id{ id }
    {
        std::cout << "Resource created with id: " << m_id << '\n';
    }

    ~Resource()
    {
        std::cout << "Destroying resource with id: " << m_id << '\n';
    }
};

int main(int, char**)
{
    kate::vector<float> l_floats(5);

    for (std::size_t index{}; index < l_floats.size(); ++index)
        l_floats[index] = 0.2f + static_cast<float>(index);

    std::cout << "Before l_steal. l_float has: " << l_floats.size() <<
        " elements\n";
    for (std::size_t index{}; index < l_floats.size(); ++index)
        std::cout << l_floats[index] << ' ';

    std::cout << std::endl;

    // kate::vector<float> l_steal(static_cast<kate::vector<float>&&>(l_floats));
    kate::vector<float> l_steal(std::move(l_floats));

    std::cout << "After l_steal. l_float has: " << l_floats.size() <<
        " elements\n";

    for (std::size_t index{}; index < l_steal.size(); ++index)
        std::cout << l_steal[index] << ' ';

    std::cout << std::endl;

    std::cout << "l_floats.at(2): ";
    l_floats.at(2);
    std::cout << std::endl;

    kate::vector<double>  doubles{ 1.3, 2.33, 5.11, -34.22, 5.22, 7.11 };

    for (std::size_t index{}; index < doubles.size(); ++index)
        std::cout << doubles[index] << ' ';

    std::cout << std::endl;

    kate::vector<std::size_t> numbers{ 22, 44, 44, 111, 451, 0xFFAB, 34, 0b11 };
    for (std::size_t index{}; index < doubles.size(); ++index)
        std::cout << numbers[index] << ' ';

    auto vec_numbers{ numbers };

    std::cout << std::endl;
    for (std::size_t index{}; index < doubles.size(); ++index)
        std::cout << numbers[index] << ' ';

    std::cout << "\n-----------------------------------------\n";

    for (std::size_t index{}; index < doubles.size(); ++index)
        std::cout << vec_numbers[index] << ' ';

    vec_numbers[4] = 65535;
    std::cout << std::endl;

    for (std::size_t index{}; index < doubles.size(); ++index)
        std::cout << vec_numbers[index] << ' ';

    std::cout << std::endl;

    std::cout << "-----------------------------------------\n";

    std::cout << "***** DOING INSERTIONS *****\n";
    kate::vector<double> real_numbers{};

    real_numbers.push_back(4.33);
    real_numbers.push_back(-1.63);
    real_numbers.push_back(2.63);
    real_numbers.push_back(8.13);
    real_numbers.push_back(-11.21);

    std::cout << "real_numbers vector current amount for elements: " << real_numbers.size() << std::endl;
    std::cout << "real_numbers vector current capacity: " << real_numbers.capacity() << std::endl;

    for (std::size_t index{}; index < real_numbers.size(); ++index)
        std::cout << real_numbers[index] << ' ';

    std::cout << std::endl;
    std::cout << "-----------------------------------------\n";

    std::cout << "***** TESTING POP_BACK *****\n";
    kate::vector<Resource> res{};

    res.push_back(Resource(44));
    res.push_back(Resource(11));
    res.push_back(Resource(66));
    res.push_back(Resource(77));
    res.push_back(Resource(88));

    for (std::size_t index{}; index < real_numbers.size(); ++index)
        std::cout << "Printing resource with id: " << res[index].m_id << '\n';

    std::cout << "Deleting resources aquired------------------------\n";
    res.pop_back();
    res.pop_back();
    res.pop_back();

    std::cout << "real_numbers vector current amount for elements: " << res.size() << std::endl;
    std::cout << "real_numbers vector current capacity: " << res.capacity() << std::endl;

    std::cout << "***** TESTING INSERTION AGAIN *****\n";
    res.push_back(Resource(44));
    res.push_back(Resource(11));
    res.push_back(Resource(66));
    res.push_back(Resource(77));

    std::cout << "real_numbers vector current amount for elements: " << res.size() << std::endl;
    std::cout << "real_numbers vector current capacity: " << res.capacity() << std::endl;

    std::cout << std::endl;
    return 0;
}
