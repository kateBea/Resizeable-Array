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
    using iterator_type         = iterator<T>;
    using const_iterator_type   = const_iterator<T>;

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

            // if we managed to allocate space we fill the array with the provided value
            if (this->m_array != nullptr)
                std::uninitialized_fill(this->m_array, this->m_array + m_count, value);
        }
        if (not this->m_array)
        {
#ifdef _DEBUG
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
    vector(std::initializer_list<value_type>&& content)
        :   m_array{ static_cast<pointer_type>(::operator new(sizeof(value_type) * content.size(), std::nothrow)) }
        ,   m_count{ content.size() }, m_capacity{ content.size() }
    {
        if (this->m_array)
            std::uninitialized_copy(content.begin(), content.end(), this->m_array);
#ifdef _DEBUG
        else
        {
            std::printf("could not allocate block of memory...");
        }
#endif
    }

    /**
     * Initialize this vector with the elements from the range within
     * first and last (exclusive) iterators, i.e. copies [first, last)
     * to this vector
     * @param first first elements from the range of elements to be copied
     * @param last last element from the range (not copied)
     * @tparam InputIterator iterator that allows to read the referenced content
     * */
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
                for (auto start{ begin() }; first != last; ++first, ++start)
                    new (start.raw()) value_type(*first);

                this->m_count = new_block_size / sizeof(value_type);
                this->m_capacity = new_block_size / sizeof(value_type);
            }
#ifdef _DEBUG
            else
            {
                std::printf("could not allocate block of memory...");
            }
#endif
        }
    }

    ///
    /// Parametrized constructor. Initialize this vector with "count"
    /// elements starting from "begin"
    ///

    /**
     * Initialize this vector with <code>count</code> elements from
     * range of elements starting at <code>first</code>. If the range contains
     * less than <code>count</code> elements the behaviour of this method is undefined
     * @param first starting point of the range of elements
     * @param count amount of elements to be copied
     * @tparam InputIterator iterator that allows to read the referenced content
     * */
    template<typename InputIterator>
    vector(InputIterator first, size_type count)
        :   m_array{ nullptr }, m_count{ count }, m_capacity{ count }
    {
        if (m_count != 0)
        {
            this->m_array = static_cast<pointer_type>(::operator new(sizeof(value_type) * count, std::nothrow));

            if (this->m_array)
            {
                for (auto start{ begin() }; start != end(); ++first, ++start)
                    new (start.raw()) value_type(*first);

                this->m_count = count;
                this->m_capacity = count;
            }
#ifdef _DEBUG
            else
            {

                std::printf("could not allocate block of memory...");
            }
#endif
        }
    }

    /**
     * Copies contents from <code>other</code> into this vector
     * @param other copied from vector
     * */
    vector(const vector& other)
        :   m_array{ nullptr }, m_count{}, m_capacity{}
    {
        if (other.size() != 0)
        {
            this->m_array = static_cast<pointer_type>(::operator new(sizeof(value_type) * other.m_count, std::nothrow));

            if (this->m_array)
            {
                std::copy(other.begin().raw(), other.end().raw(), this->m_array);
                this->m_count = other.size();
                this->m_capacity = other.capacity();
            }
#ifdef _DEBUG
            else
            {
                std::printf("could not allocate block of memory...");
            }
#endif
        }
    }

    /**
     * Copy the contents of <code>other</code> into this vector
     * @param other copied from vector
     * */
    vector& operator=(const vector& other)
    {
        if (this != &other)
        {
            for (size_type index{}; index < m_count; ++index)
                this->m_array[index].~value_type();
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

    /**
     * Moves the contents of the <code>other</code> vector
     * into this vector. After this operation <code>other</code> is put
     * into an invalid state
     * @param other moved from vector
     * */
    vector(vector&& other) noexcept
        :   m_array{ other.m_array }, m_count{ other.size() }, m_capacity{ other.capacity() }
    {
        if (other.capacity != 0)
        {
            other.m_array = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }
    }

    /**
     * Moves the contents of the <code>other</code> vector
     * into this vector. After this operation <code>other</code> is put
     * into an invalid state
     * @param other moved from vector
     * */
    vector& operator=(vector&& other) noexcept
    {
        if (this != &other)
        {
            this->m_array = other.m_array;
            this->m_count = other.size();
            this->m_capacity = other.capacity();

            other.m_array = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }

        return *this;
    }

    /**
     * Returns a pointer to the block holding the underlying buffer of data
     * @return pointer to the elements
     * */
    constexpr auto data() -> pointer_type
    {
        return m_array;
    }

    /**
     * Calls the destructor for all the contained elements
     * in this vector and frees the underlying buffer of memory
     * */
    ~vector()
    {
        // pre clean-up
        for (size_type index{}; index < m_count; ++index)
            this->m_array[index].~T();

        ::operator delete(this->m_array);
    }

    /**
     * Returns the total count of elements of this vector
     * @return total elements contained within this vector
     * */
     [[nodiscard]]
    auto size() const -> size_type
    {
        return this->m_count;
    }

    /**
     * Returns the number of elements this vector has allocated space for
     * @return capacity of this vector
     * */
    [[nodiscard]]
    auto capacity() const -> size_type
    {
        return this->m_capacity;
    }

    /**
     * Returns <code>true</code> if this vector has no elements,
     * returns <code>false</code> otherwise
     * */
    [[nodiscard]]
    auto empty() const -> bool
    {
        return size() == 0;
    }

    /**
     * Returns a reference to the first element of this vector
     * @return reference to first element
     * */
    [[nodiscard]]
    auto operator[](size_type index) -> reference_type
    {
#ifdef _DEBUG
        assert(index < this->m_count && "Attempting to derefenrence out of bounds index element...");
#endif
        return (*this)[index];
    }

    ///
    /// Returns constant reference to element at postion "index"
    ///

    /**
     * Returns a constant reference to the element at index <code>index</code>
     * @param index index of the element to be returned
     * @return reference to the element at the given index
     * */
    auto operator[](size_type index) const -> const_reference_type
    {
#ifdef _DEBUG
        assert(index < this->m_count && "Attempting to derefenrence out of bounds index element...");
#endif
        return (*this)[index];
    }

    ///
    /// Return reference to element at postion "index" throws "out_of_bounds"
    /// exception if index is not within the range of valid elements
    /// or "empty_vector" if the vector has no elements
    ///

    /**
     * Return reference to element at position <code>index</code>
     * @param index index of the element to be returned
     * @return reference to the element at the given index
     * @throws std::runtime_error if this vector is empty or the index is out of bounds
     * */
    auto at(size_type index) -> reference_type
    {
        if (size() == 0)
            throw std::runtime_error("This vector has no elements");

        if (index >= size())
            throw std::out_of_range("Attempting to access an element out of range");

        return (*this)[index];
    }

    /**
     * Return constant reference to element at position <code>index</code>
     * @param index index of the element to be returned
     * @return constant reference to the element at the given index
     * @throws std::runtime_error if this vector is empty or the index is out of bounds
     * */
    auto at(size_type index) const -> const_reference_type
    {
        if (size() == 0)
            throw std::runtime_error("This vector has no elements");

        if (index >= size())
            throw std::out_of_range("Attempting to access an element out of range");

        return (*this)[index];
    }

    ///
    /// Reserve a block of memory to hold at least count elements
    /// Has no effect if the container can already hold new_count elements i.e.
    /// this->capacity() is equal or greater to new_count
    ///
    auto reserve(size_type new_count) -> void
    {
        // TODO: how should this function behave when theres elements
        // TODO: how should this function behave when theres no elements

        // TODO: how should this function behave when capacity is 0
        // TODO: how should this function behave when capacity is is not 0
        if (new_count > capacity())
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

    /**
     * Construct element in place, in this case, right
     * at the end of this vector. This function takes the necessary
     * arguments to construct a new object of the type held by this vector
     * @param args arguments to construct the new object
     * @tparam types of the parameters of this function
     * */
    template <typename... Args>
    auto emplace_back(Args&&... args) -> void
    {
        if (size() == capacity())
            reallocate();

        new(&this->m_array[this->m_count++]) value_type(std::forward<Args>(args)...);
    }

    ///
    /// Concatenate the contents of this vector and "other"
    /// This vector contains the result of the concatenation
    ///
    auto append(const vector& other) -> void
    {
        if (!other.empty())
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
     [[nodiscard]]
    constexpr auto begin() noexcept -> iterator_type
    {
        return iterator_type{ this->m_array };
    }

    /**
     * Returns an iterator past the last element of the vector
     * @return access to the element past the end of this vector
     * */
    [[nodiscard]]
    constexpr auto end() noexcept -> iterator_type
    {
        return iterator_type{ this->m_array + this->m_count };
    }

    /**
     * Returns a constant iterator to the beginning of the vector
     * @return read-only access to the elements at the beginning
     * */
    [[nodiscard]]
    constexpr auto begin() const noexcept -> const_iterator_type
    {
        return const_iterator_type{ this->m_array };
    }

    /**
     * Returns a constant iterator past the last element of the vector
     * @return read-only access to the element past the end of this vector
     * */
    [[nodiscard]]
    constexpr auto end() const noexcept -> const_iterator_type
    {
        return const_iterator_type{ this->m_array + this->m_count };
    }

    /**
     * Returns a constant iterator to the beginning of the vector
     * @return read-only access to the elements at the beginning
     * */
    [[nodiscard]]
    constexpr auto cbegin() const noexcept -> const_iterator_type
    {
        return const_iterator_type{ this->m_array };
    }

    /**
     * Returns a constant iterator past the last element of the vector
     * @return read-only access to the element past the end of this vector
     * */
    [[nodiscard]]
    constexpr auto cend() const noexcept -> const_iterator_type
    {
        return const_iterator_type{ this->m_array + this->m_count };
    }

    /**
     * Returns a reference to the first element of this vector
     * @return front element
     * */
    [[nodiscard]]
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
