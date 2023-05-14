#ifndef ITERATOR_HH
#define ITERATOR_HH

#include <cstdint>

template<typename T>
class iterator
{
public:
    using size_type             = std::size_t;
    using pointer_type          = T*;
    using reference_type        = T&;

    explicit iterator(pointer_type ptr) : p{ ptr } { }

    // prefix increment
    auto operator++() -> iterator
    {
        ++p;
        return *this;
    }

    // postfix increment
    auto operator++(int) -> iterator
    {
        auto res{ p };
        ++p;
        return iterator{ res };
    }

    // prefix increment
    auto operator--() -> iterator
    {
        --p;
        return *this;
    }

    // postfix increment
    auto operator--(int) -> iterator
    {
        auto res{ p };
        --p;
        return iterator{ res };
    }

    auto operator+(size_type count) -> iterator
    {
        return iterator{ this->p + count };
    }

    auto operator-(size_type count) -> iterator
    {
        return iterator{ this->p - count };
    }

    auto operator-(iterator other) -> size_type
    {
        return this->p > other.p ?
               (this->p - other.p) : (other.p - this->p);
    }

    auto operator!=(const iterator& other) -> bool
    {
        return this->p != other.p;
    }

    auto operator==(const iterator& other) -> bool
    {
        return this->p == other.p;
    }

    auto operator*() -> reference_type { return *p; }
    auto operator->() -> pointer_type { return p; }

    auto raw() const -> pointer_type { return p; }

private:
    pointer_type p{};
};

#endif // ITERATOR_HH
