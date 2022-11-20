#ifndef VECTOR_HH
#define VECTOR_HH

#include <cstdio>
#include <new>
#include <cstring>
#include <exception>
#include <cstdint>
#include <utility>
#include <initializer_list>
#include <string_view>
#include <algorithm>

#include <memory>

#define DEBUG_LOG(log_str)  std::cerr << log_str << '\n'

namespace kt
{
template
<typename T, typename alloc = std::allocator<T>>
class vector
{
public:
    using size_type             = std::size_t;
    using pointer_type          = T*;
    using const_reference       = const T&;
    using pointer_to_const_type = const T*;

    ///
    /// default constructor
    ///
    vector()
        :   m_array{ nullptr }, m_count{}, m_capacity{}
    {

    }

    ///
    /// parametrized constructor. Reserve space to hold at least "count" elements
    ///
    vector(size_type count)
        :   m_array{ nullptr }, m_count{ 0 }, m_capacity{ count }
    {
        if (count != 0)
            this->m_array = static_cast<pointer_type>(::operator new(sizeof(T) * count, std::nothrow));
    }

    ///
    /// parametrized constructor. Initializes vector
    /// with the elements from the "content"
    ///
    vector(std::initializer_list<T>&& content)
        :   m_array{ static_cast<pointer_type>(::operator new(sizeof(T) * content.size(), std::nothrow)) },
            m_count{ content.size() }, m_capacity{ content.size() }
    {
        if (this->m_array)
            std::copy(content.begin(), content.end(), this->m_array);
    }

    ///
    /// copy constructor. Initialize this vector with elements of "other"
    ///
    vector(const vector& other)
        :   m_array{ nullptr }, m_count{}, m_capacity{}
    {
        if (other.m_count != 0)
        {
            this->m_array = static_cast<pointer_type>(::operator new(sizeof(T) * other.m_count, std::nothrow));


            this->m_count = other.m_count;
            this->m_capacity = other.m_capacity;

            if (this->m_array != nullptr)
                std::copy(other.m_array, other.m_array + other.m_count, this->m_array);
        }
    }

    ///
    /// assigment operator. Deep copy of p_vector
    ///
    vector& operator=(const vector& other)
    {
        if (this != &other)
        {
            // clean up previous block
            for (size_type index{}; index < m_count; ++index)
                this->m_array[index].~T();
            ::operator delete(this->m_array);

            this->m_array = static_cast<pointer_type>(::operator new(sizeof(T) * other.m_count, std::nothrow));
            this->m_count = other.m_count;
            this->m_capacity = other.m_capacity;

            if (this->m_array)
                std::copy(other.m_array, other.m_array + other.m_count, this->m_array);
        }

        return *this;
    }

    ///
    /// move constructor
    ///
    vector(vector&& other)
        :   m_array{ other.m_array }, m_count{ other.m_count }, m_capacity{ other.m_capacity }
    {
        if (other.m_capacity != 0)
        {
            other.m_array = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }
    }

    ///
    /// destructor
    ///
    ~vector()
    {
        // cleanup
        for (size_type index{}; index < m_count; ++index)
            this->m_array[index].~T();

        ::operator delete(this->m_array);
        // delete[] this->m_array;
    }

    ///
    /// assigment operator
    ///
    vector& operator=(vector&& other)
    {
        if (this != &other)
        {
            this->m_array = other.m_array;
            this->m_count = other.m_count;
            this->m_capacity = other.m_capacity;

            other.m_array = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }

        return *this;
    }

    ///
    /// amount of elements in the vector
    ///
    auto size() const -> size_type
    {
        return this->m_count;
    }

    ///
    /// returns the size of the block of memory held by the vector
    ///
    auto capacity() const -> size_type
    {
        return this->m_capacity;
    }

    ///
    /// return true if the vector is has no elements
    ///
    auto empty() const -> bool
    {
        return this->m_count == 0;
    }

    ///
    /// return reference to element at postion "index"
    ///
    auto operator[](size_type index) -> T&
    {
        return this->m_array[index];
    }

    ///
    /// return constant reference to element at postion "index"
    ///
    auto operator[](size_type index) const -> const_reference
    {
        return this->m_array[index];
    }

    ///
    /// return constant reference to element at postion "index"
    /// throws exceptions if index is not valid or vector is empty
    ///
    auto at(size_type index) -> T&
    {
        try
        {
            if (this->m_count == 0)
                throw empty_vector{};
            if (not (index > 0 and index < this->m_count))
                throw out_of_bounds{};

        }
        catch (const out_of_bounds& oob) { std::printf("%s", oob.what()); }
        catch (const empty_vector& ema) { std::printf("%s", ema.what()); }
        catch(...) { std::printf("Other exceptions thrown"); }

        return this->m_array[index];
    }

    ///
    /// return constant reference to element at postion "index"
    /// throws exceptions if index is not valid or vector is empty
    ///
    auto at(size_type index) const -> const_reference
    {
        try
        {
            if (this->m_count == 0)
                throw empty_vector{};
            if (not (index > 0 and index < this->m_count))
                throw out_of_bounds{};

        }
        catch (const out_of_bounds& oob) { std::printf("%s", oob.what()); }
        catch (const empty_vector& ema) { std::printf("%s", ema.what()); }
        catch(...) { std::printf("Other exceptions thrown"); }

        return this->m_array[index];
    }

    ///
    /// reserve a block of memory
    ///
    auto reserve(size_type count) -> void
    {
        // TODO

        // this function can be called at any point and
        // state of the vector in the program

    }

    ///
    /// Insert one element at the end of the vector
    ///
    auto push_back(const T& info) -> void
    {
        // if capacity == count:
        // allocate new block
        // copy data from old block to new block
        // add new data
        // delete old block

        // otherwise (capacity > count)
        // put new element at the end
        // increase count by 1
        if (this->m_capacity > this->m_count)
        {
            this->m_array[this->m_count] = info;
            this->m_count += 1;
        }
        else
        {
            reallocate();

            this->m_array[this->m_count] = info;
            this->m_count += 1;
        }
    }

    ///
    /// Insert one element at the end of the vector
    /// with support on move semantics
    ///
    auto push_back(T&& info) -> void
    {
        // if capacity == count:
        // allocate new block
        // copy data from old block to new block
        // add new data
        // delete old block

        // otherwise (capacity > count)
        // put new element at the end
        // increase count by 1
        if (this->m_capacity > this->m_count)
        {
            m_array[this->m_count] = std::move(info);
            this->m_count += 1;
        }
        else
        {
            reallocate();

            this->m_array[this->m_count] = std::move(info);
            this->m_count += 1;
        }
    }

    ///
    /// Remove the last element from the vector
    ///
    auto pop_back() -> void
    {
        if (m_count != 0)
        {
            m_array[m_count - 1].~T();
            m_count -= 1;

        }

    }

    ///
    /// Remove all elements of the vector
    ///
    auto clear() -> void
    {
        std::for_each(this->m_array, this->m_array + this->m_count, [](T& info) -> void { info.~T(); });

        // std::destroy_n(this->m_array, this->m_count);

        // for (size_type index{}; index < m_count; ++index)
        //     this->m_array[index].~T();

        this->m_count = 0;
    }

    ///
    /// Ajust vector to contain count elements
    ///
    auto resize(size_type count) -> void;

    ///
    /// Returns a pointer to the beginning of the vector
    ///
    auto begin() -> pointer_type
    {
        return &(this->m_array[0]);
    }

    ///
    /// Returns a pointer to the end of the vector
    ///
    auto end() -> pointer_type
    {
        return &(this->m_array[this->m_count]);
    }

    ///
    /// Returns a pointer to the beginning of the vector
    ///
    auto cbegin() const -> pointer_to_const_type
    {
        return &(this->m_array[0]);
    }

    ///
    /// Returns a pointer to the end of the vector
    ///
    auto cend() const -> pointer_to_const_type
    {
        return &(this->m_array[this->m_count]);
    }

private:
    static constexpr size_type grow_factor{ 2 };

    void reallocate()
    {
        size_type new_block_size{ (!this->m_capacity) ? 1 : (m_capacity * grow_factor) };
        pointer_type new_block{ static_cast<pointer_type>(::operator new(sizeof(T) * new_block_size, std::nothrow)) };

        if (not new_block)
        {
            std::printf("Failed to allocate new block of memory");
            return;
        }

        std::copy(this->m_array, this->m_array + this->m_count, new_block);

        ::operator delete(static_cast<void*>(this->m_array));

        this->m_array = new_block;
        this->m_capacity = new_block_size;

    }

    class out_of_bounds : public std::exception
    {
    public:
        out_of_bounds() = default;
        ~out_of_bounds() = default;

        const char* what() const noexcept override
        {
            return this->m_exc.data();
        }

    private:
        std::string_view m_exc{ "[out_of_bounds]: Index out of bounds\n" };
    };

    class empty_vector : public std::exception
    {
    public:
        empty_vector() = default;
        ~empty_vector() = default;

        const char* what() const noexcept override
        {
            return this->m_exc.data();
        }

    private:
        std::string_view m_exc{ "[empty_vector]: vector has no elements\n" };
    };

    pointer_type m_array;
    size_type m_count;
    size_type m_capacity;

    // CONSTRAINTS:
    // m_capacity >= m_count >= 0
};

}   // END KATE NAMESPACE

#endif
