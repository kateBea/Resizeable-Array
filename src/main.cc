#include "vector.h"
#include <iostream>

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
    kt::vector<float> vector1(5);

    for (std::size_t index{}; index < vector1.size(); ++index)
        vector1[index] = 0.2f + static_cast<float>(index);

    std::cout << "Before vector2's construction vector1 has: " << vector1.size() << " elements\n";

    for (std::size_t index{}; index < vector1.size(); ++index)
        std::cout << vector1[index] << ' ';

    std::cout << std::endl;

    kt::vector<float> vector2(std::move(vector1));

    std::cout << "After vector2's construction vector1 has: " << vector1.size() << " elements\n";

    for (std::size_t index{}; index < vector2.size(); ++index)
        std::cout << vector2[index] << ' ';

    std::cout << std::endl;

    std::cout << "vector1.at(2): ";
    vector1.at(2);
    std::cout << std::endl;

    kt::vector<double>  doubles{ 1.3, 2.33, 5.11, -34.22, 5.22, 7.11 };

    for (std::size_t index{}; index < doubles.size(); ++index)
        std::cout << doubles[index] << ' ';

    std::cout << std::endl;

    kt::vector<std::size_t> numbers{ 22, 44, 44, 111, 451, 0xFFAB, 34, 0b11 };
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
    kt::vector<double> real_numbers{};

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
    kt::vector<Resource> res{};

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

    std::cout << "res vector current amount for elements: " << res.size() << std::endl;
    std::cout << "res vector current capacity: " << res.capacity() << std::endl;

    std::cout << "***** TESTING INSERTION AGAIN WITH MOVE SEMANTICS *****\n";

    res.push_back(Resource(44));
    res.push_back(Resource(11));
    res.push_back(Resource(66));
    res.push_back(Resource(77));

    res.push_back(std::move(Resource(44)));
    res.push_back(std::move(Resource(11)));
    res.push_back(std::move(Resource(66)));
    res.push_back(std::move(Resource(77)));

    std::cout << "res vector current amount for elements: " << res.size() << std::endl;
    std::cout << "res vector current capacity: " << res.capacity() << std::endl;

    std::cout << "***** CALL TO KATE::VECTOR::CLEAR *****\n";
    res.clear();
    std::cout << "res vector current amount for elements: " << res.size() << std::endl;
    std::cout << "res vector current capacity: " << res.capacity() << std::endl;

    std::cout << "****** RANGED FOR KATE::VECTOR ******" << std::endl;
    kt::vector<double> reales{ 3.44, 5.22, -5.66, 8.11, 9.23, 10.34 };

    std::cout << "CONST RANGED-FOR:     ";
    for (const auto& it : reales)
        std::cout << it << ' ';

    std::cout << std::endl << "NON-CONST RANGED-FOR: ";
    for (auto& it : reales)
        std::cout << it << ' ';

    std::cout << std::endl;

    std::cout << "****** TESTING CONSTRUCTOR WITH ITERATORS ******" << std::endl;
    kt::vector<double> vector3{ 3.44, 5.22, -5.66, 8.11, 9.23, 10.34 };
    const kt::vector<double> vector3copy(vector3.begin(), vector3.end());

    for (auto& it : vector3)
        std::cout << it << ' ';

    std::cout << std::endl;
    
    for (const auto& it : vector3copy)
        std::cout << it << ' ';


    std::cout << std::endl;
    return 0;
}
