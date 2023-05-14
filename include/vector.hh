#ifndef VECTOR_HH
#define VECTOR_HH

#include "common.hh"
#include "iterator.hh"
#include "const_iterator.hh"

NAMESPACE_KT_BEG

template <typename T>
class vector
{
public:
    using value_type            = T;
    using size_type             = std::size_t;
    using reference_type        = T&;
    using pointer_type          = T*;
    using const_reference_type  = const T&;
    using c_string_type         = const char*;
    using iterator_type         = iterator<value_type>;
    using const_iterator_type   = const_iterator<value_type>;

    /**
     * Default constructs this vector with initial size of 0
     * and initial capacity of 0
     * */
    explicit
    vector() noexcept
        :   m_array{ nullptr }, m_count{}, m_capacity{}
    {}

    /**
     * Initializes this vector with <code>count</code> copies of
     * the value <code>value</code>
     * @param count amount of copies to be made
     * @param value initial value for ech copy
     */
    explicit
    vector(size_type count, const value_type& value = value_type())
        :   m_array{ nullptr }, m_count{ count }, m_capacity{ count }
    {
        if (m_count != 0) {
            this->m_array = static_cast<pointer_type>(::operator new(sizeof(value_type) * count, std::nothrow));

            // if we managed to allocate space we fill the array
            // with the provided value
            if (this->m_array != nullptr)
                std::uninitialized_fill(this->m_array, this->m_array + m_count, value);
        }
        if (not this->m_array)
        {
#if _DEBUG
            std::printf("could not allocate block of memory...");
#endif
            this->m_capacity = 0;
        }
    }

    /**
     * Constructs and initializes this vector with the elements with in the
     * range of the <b>std::initializer_list</b>
     * @param content range of elements to initialize this vector with
     * */
    vector(std::initializer_list<T>&& content)
        :   m_array{ static_cast<pointer_type>(::operator new(sizeof(value_type) * content.size(), std::nothrow)) }
        ,   m_count{ content.size() }, m_capacity{ content.size() }
    {
        if (this->m_array)
            std::copy(content.begin(), content.end(), this->m_array);
#if _DEBUG
        else
        {
            std::printf("could not allocate block of memory...");
        }
#endif
    }

    ///
    /// Parametrized constructor. Initialize this vector with elements
    /// within the ranged given by "first" and "last"
    ///
    template<typename InputIterator>
    vector(InputIterator first, InputIterator last)
        :   m_array{ nullptr }, m_count{}, m_capacity{}
    {
        // represents the amount of bytes between first and last
        size_type new_block_size{ sizeof(value_type) * (last - first) };

        if (new_block_size != 0)
        {
            // new_block_size represents the size in bytes of the new block
            this->m_array = static_cast<pointer_type>(::operator new(new_block_size, std::nothrow));

            if (this->m_array)
            {
                std::memcpy(static_cast<void*>(this->m_array), static_cast<const void*>(first.raw()),
                    new_block_size);
                this->m_count = new_block_size / sizeof(value_type);
                this->m_capacity = new_block_size / sizeof(value_type);

            }
            else
            {
                std::printf("could not allocate block of memory...");
            }
        }
    }

    ///
    /// Parametrized constructor. Initialize this vector with "count"
    /// elements starting from "begin"
    ///
    vector(iterator_type first, size_type count)
        :   m_array{ nullptr }, m_count{ count }, m_capacity{ count }
    {
        // TODO: still needs testing
        if (count != 0)
        {
            this->m_array = static_cast<pointer_type>(::operator new(sizeof(value_type) * count, std::nothrow));

            if (this->m_array)
            {
                std::memcpy(static_cast<void*>(this->m_array), static_cast<const void*>(first.raw()),
                    count * sizeof(value_type));
                // std::copy(first.raw(), first.raw() + count, this->m_array);
                this->m_count = count;
                this->m_capacity = count;
            }
            else
            {
                std::printf("could not allocate block of memory...");
                this->m_count = 0;
                this->m_capacity = 0;
            }
        }
    }

    ///
    /// Copy constructor. Initialize this vector with elements from "other"
    ///
    vector(const vector& other)
        :   m_array{ nullptr }, m_count{}, m_capacity{}
    {
        if (other.m_count != 0)
        {
            this->m_array = static_cast<pointer_type>(::operator new(sizeof(value_type) * other.m_count, std::nothrow));

            if (this->m_array)
            {
                std::memcpy(static_cast<void*>(this->m_array), static_cast<const void*>(other.m_array),
                    other.m_count * sizeof(value_type));
                // std::copy(other.m_array, other.m_array + other.m_count, this->m_array);
                this->m_count = other.m_count;
                this->m_capacity = other.m_capacity;
            }
            else
            {
                std::printf("could not allocate block of memory...");
                this->m_count = 0;
                this->m_capacity = 0;
            }
        }
    }

    ///
    /// Assigment operator. Deep copy of "other"
    ///
    vector& operator=(const vector& other)
    {
        if (this != &other)
        {
            // clean up previous block
            for (size_type index{}; index < m_count; ++index)
                this->m_array[index].~T();
            ::operator delete(this->m_array);

            this->m_array = static_cast<pointer_type>(::operator new(sizeof(value_type) * other.m_count, std::nothrow));

            if (this->m_array)
            {
                std::memcpy(static_cast<void*>(this->m_array), static_cast<const void*>(other.m_array),
                    other.m_count * sizeof(value_type));
                // std::copy(other.m_array, other.m_array + other.m_count, this->m_array);
                this->m_count = other.m_count;
                this->m_capacity = other.m_capacity;
            }
            else
                std::printf("could not allocate block of memory...");
        }

        return *this;
    }

    ///
    /// Move constructor
    ///
    vector(vector&& other) noexcept
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
    /// Destructor
    ///
    ~vector()
    {
        // cleanup
        for (size_type index{}; index < m_count; ++index)
            this->m_array[index].~T();

        ::operator delete(this->m_array);
    }

    ///
    /// Assigment operator
    ///
    vector& operator=(vector&& other) noexcept
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

    /**
     * Returns the total count of elements of this vector
     * @return total elements contained within this vector
     * */
    auto size() const -> size_type
    {
        return this->m_count;
    }

    /**
     * Returns the number of elements this vector has allocated space for
     * @return capacity of this vector
     * */
    auto capacity() const -> size_type
    {
        return this->m_capacity;
    }

    ///
    /// Return true if this vector has no elements, fase otherwise
    ///
    auto empty() const -> bool
    {
        return this->m_count == 0;
    }

    ///
    /// Returns reference to element at postion "index"
    ///
    auto operator[](size_type index) -> reference_type
    {
#ifdef _DEBUG
        assert(index < this->m_count && "Attempting to derefenrence out of bounds index element...");
#endif
        return this->m_array[index];
    }

    ///
    /// Returns constant reference to element at postion "index"
    ///
    auto operator[](size_type index) const -> const_reference_type
    {
#ifdef _DEBUG
        assert(index < this->m_count && "Attempting to derefenrence out of bounds index element...");
#endif
        return this->m_array[index];
    }

    ///
    /// Return reference to element at postion "index" throws "out_of_bounds"
    /// exception if index is not within the range of valid elements
    /// or "empty_vector" if the vector has no elements
    ///
    auto at(size_type index) -> reference_type
    {
        try
        {
            if (this->m_count == 0)
                throw empty_vector{};
            if (not (index < this->m_count))
                throw out_of_bounds{};

        }
        catch (const out_of_bounds& oob)
        {
            std::printf("%s", oob.what());
        }
        catch (const empty_vector& ema)
        {
            std::printf("%s", ema.what());
        }
        catch(...)
        {
            std::printf("Other exceptions thrown");
        }

        return this->m_array[index];
    }

    ///
    /// Return constant reference to element at postion "index" throws "out_of_bounds"
    /// exception if index is not within the range of valid elements or "empty_vector"
    /// if the vector has no elements
    ///
    auto at(size_type index) const -> const_reference_type
    {
        try
        {
            if (this->m_count == 0)
                throw empty_vector{};
            if (not (index < this->m_count))
                throw out_of_bounds{};

        }
        catch (const out_of_bounds& oob)
        {
            std::printf("%s", oob.what());
        }
        catch (const empty_vector& ema)
        {
             std::printf("%s", ema.what());
        }
        catch(...)
        {
            std::printf("Other exceptions thrown");
        }

        return this->m_array[index];
    }

    ///
    /// Reserve a block of memory to hold at least count elements
    /// Has no effect if the container can already hold new_count elements i.e.
    /// this->capacity() is equal or greater to new_count
    ///
    auto reserve(size_type new_count) -> void
    {
        if (new_count > this->m_capacity)
        {
            this->m_capacity = new_count;
            reallocate();
        }
    }

    ///
    /// Adjust vector to contain count elements
    ///
    auto resize(size_type count) -> void
    {

    }

    ///
    /// Insert elements at the end
    ///
    template <typename... Args>
    auto emplace_back(Args&&... args) -> void
    {
        if (this->m_count == this->m_capacity)
            reallocate();

        // construct in place
        new(&this->m_array[this->m_count++]) value_type(std::forward<Args>(args)...);
    }

    ///
    /// Concatenate the contents of this vector and "other"
    /// This vector contains the result of the concatenation
    ///
    auto append(const vector& other) -> void
    {
        if (not other.empty())
        {
            pointer_type new_block{ static_cast<pointer_type>
                (::operator new(sizeof(value_type) * (this->m_count + other.m_count), std::nothrow)) };

            if (new_block)
            {
                std::memcpy(static_cast<void*>(new_block), static_cast<const void*>(this->m_array),
                    this->m_count * sizeof(value_type));
                std::memcpy(static_cast<void*>(new_block + this->m_count), static_cast<const void*>(other.m_array),
                    other.m_count * sizeof(value_type));

                ::operator delete(static_cast<void*>(this->m_array));

                this->m_array = new_block;
                this->m_count = this->m_count + other.m_count;
                this->m_capacity = this->m_count + other.m_count;

            }
            else
            {
                std::printf("failed to concatenate. Could not allocate block of memory...");
                return;
            }
        }
    }

    ///
    /// Destroy the last n elements. If there is less than
    /// count elements, it empties the vector
    ///
    auto remove_n(size_type count) -> void
    {
        if (count < this->m_count)
        {
            // if we have more than count elements
            std::for_each(this->m_array,
                this->m_array + count, [](reference_type info) -> void { info.~T(); });

            this->m_count -= count;
        }
        else
        {
            // if we have less than count elements
            std::for_each(this->m_array,
                this->m_array + this->m_count, [](reference_type info) -> void { info.~T(); });

            this->m_count = 0;
        }
    }

    ///
    /// Insert one element at the end of the vector
    ///
    auto push_back(const_reference_type info) -> void
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
            new(&this->m_array[this->m_count]) value_type(info);
            this->m_count += 1;
        }
        else
        {
            reallocate();

            // if reallocate fails, m_count will remain same as m_capacity
            // preventing from appending new element
            if (this->m_capacity == this->m_count)
            {
                std::printf("could not insert new element due to error while reallocating...");
                return;
            }

            new(&this->m_array[this->m_count]) value_type(info);
            this->m_count += 1;
        }
    }

    ///
    /// Insert one element at the end of the vector
    /// with support for move semantics
    ///
    auto push_back(value_type&& info) -> void
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
            new(&this->m_array[this->m_count]) value_type(std::move(info));
            this->m_count += 1;
        }
        else
        {
            reallocate();

            // if reallocate fails, m_count will remain same as m_capacity
            // preventing from appending new element
            if (this->m_capacity == this->m_count)
            {
                std::printf("could not insert new element due to error while reallocating...");
                return;
            }

            new(&this->m_array[this->m_count]) value_type(std::move(info));
            ++(this->m_count);
        }
    }

    /**
     * Remove the last element of this vector
     * */
    auto pop_back() -> void
    {
        if (this->m_count != 0)
        {
            this->m_array[this->m_count - 1].~T();
            --(this->m_count);
        }

    }

    /**
     * Remove all the elements from this vector
     * */
    auto clear() -> void
    {
        std::for_each(this->m_array, this->m_array + this->m_count, [](T& info) -> void { info.~T(); });
        this->m_count = 0;
    }

    /**
     * Returns an iterator to the beginning of the vector
     * @return access to the elements at the beginning
     * */
    constexpr auto begin() noexcept -> iterator_type
    {
        return iterator{ this->m_array };
    }

    /**
     * Returns an iterator past the last element of the vector
     * @return access to the element past the end of this vector
     * */
    constexpr auto end() noexcept -> iterator_type
    {
        return iterator{ this->m_array + this->m_count };
    }

    /**
     * Returns a constant iterator to the beginning of the vector
     * @return read-only access to the elements at the beginning
     * */
    constexpr auto begin() const noexcept -> const_iterator_type
    {
        return const_iterator{ this->m_array };
    }

    /**
     * Returns a constant iterator past the last element of the vector
     * @return read-only access to the element past the end of this vector
     * */
    constexpr auto end() const noexcept -> const_iterator_type
    {
        return const_iterator{ this->m_array + this->m_count };
    }

    /**
     * Returns a constant iterator to the beginning of the vector
     * @return read-only access to the elements at the beginning
     * */
    constexpr auto cbegin() const noexcept -> const_iterator_type
    {
        return const_iterator{ this->m_array };
    }

    /**
     * Returns a constant iterator past the last element of the vector
     * @return read-only access to the element past the end of this vector
     * */
    constexpr auto cend() const noexcept -> const_iterator_type
    {
        return const_iterator{ this->m_array + this->m_count };
    }

    ///
    /// Returns a reference to the first element of the vector
    ///
    auto front() noexcept -> reference_type 
    {
        return *this->m_array;
    }

    ///
    /// Returns a reference to the last element of the vector
    ///
    auto back() noexcept -> reference_type 
    {
        return *(this->m_array + this->m_count - 1);
    }

    ///
    /// Returns a reference to the first element of the vector
    ///
    auto front() const noexcept -> const_reference_type 
    {
        return *this->m_array;
    }

    ///
    /// Returns a reference to the last element of the vector
    ///
    auto back() const noexcept -> const_reference_type 
    {
        return *(this->m_array + this->m_count - 1);
    }

private:
    static constexpr size_type grow_factor{ 2 };

    void reallocate()
    {
        size_type new_block_count{ (!this->m_capacity) ? 1 : (this->m_capacity * grow_factor) };
        pointer_type new_block{ static_cast<pointer_type>(::operator new(sizeof(T) * new_block_count, std::nothrow)) };

        if (not new_block)
        {
            std::printf("Failed to allocate new block of memory");
            return;
        }

        // TODO: pending to change to std::copy, same goes for some constructors
        std::memcpy(static_cast<void*>(new_block), static_cast<const void*>(this->m_array),
            this->m_count * sizeof(value_type));

        ::operator delete(static_cast<void*>(this->m_array));

        this->m_array = new_block;
        this->m_capacity = new_block_count;

    }

    class out_of_bounds : public std::exception
    {
    public:
        out_of_bounds() = default;
        ~out_of_bounds() = default;

        auto what() const noexcept -> c_string_type override
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

        auto what() const noexcept -> c_string_type override
        {
            return this->m_exc.data();
        }

    private:
        std::string_view m_exc{ "[empty_vector]: vector has no elements\n" };
    };

    pointer_type    m_array;
    size_type       m_count;
    size_type       m_capacity;

    // CONSTRAINTS:
    // m_capacity >= m_count >= 0

    // DETAILS:
    // value_type must support the operations for 
    // copy assignmet or move assigment

    // m_capacity points to the underlying memory buffer owned by 
    // this vector or its value is nullptr

    // m_capacity is increased by a grow factor to minimise reallocations

    // m_count keeps track of the amount of elements already held
    // inside the vector
};

NAMESPACE_KT_END   // END KT NAMESPACE

#endif
