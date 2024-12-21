#pragma once

#include <cstddef>
#include <iterator>
#include <memory_resource>
#include <type_traits>

#define MIN_CAP static_cast<size_t>(10)

template< typename T, typename allocator_type = std::pmr::polymorphic_allocator<T> >
class Stack {
private:
    template< bool IsConst >
    class BaseIterator {
        friend Stack;
    public:
        using value_type = T;
        using reference_type = std::conditional_t<IsConst, const T&, T&>;
        using pointer_type = std::conditional_t<IsConst, const T*, T*>;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
    private:
        pointer_type cur_;
    private:
        BaseIterator() noexcept
         : cur_(nullptr)
        {}
        
        explicit BaseIterator(pointer_type ptr) noexcept
         : cur_(ptr)
        {}
    public:
        template <bool B = IsConst, typename = std::enable_if_t<B>>
        BaseIterator(const BaseIterator<false>& other) noexcept
         : cur_(other.cur_)
        {}

        inline bool operator==(const BaseIterator& other) const noexcept {
            return this->cur_ == other.cur_;
        }

        inline bool operator!=(const BaseIterator& other) const noexcept {
            return this->cur_ != other.cur_;
        }

        reference_type operator*() const noexcept {
            return *this->cur_;
        }

        pointer_type operator->() const noexcept {
            return &(*this->cur_);
        }

        BaseIterator& operator++() noexcept {
            --this->cur_;
            return *this;
        }

        BaseIterator operator++(int) noexcept {
            BaseIterator copy = *this;
            ++this->cur_;
            return copy;
        }
    };
public:
    using Iterator = BaseIterator<false>;
    using ConstIterator = BaseIterator<true>;

private:
    allocator_type allocator_;
    size_t sz_;
    size_t cap_;
    T* data_;

    using allocator_traits = std::allocator_traits<allocator_type>;
public:
    /* Инициализация, копирование и уничтожение */

    // Конструктор по умолчанию
    explicit Queue(const allocator_type& alloc = {}) noexcept
     : allocator_(alloc)
     , sz_(0)
     , cap_(0)
     , data_(nullptr)
    {}

    // Конструктор копирования
    Stack(const Stack& other, const allocator_type& alloc = {})
     : allocator_(alloc)
     , sz_(other.sz_)
     , cap_(other.sz_)
     , data_(allocator_.allocate(other.sz_))
    {
        for (size_t i = 0; i < this->sz_; ++i) {
            try {
                this->allocator_.construct(this->data_ + i, other.data_[i]);
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    allocator_traits::destroy(this->allocator_, this->data_ + j);
                }
                this->allocator_.deallocate(this->data_, this->cap_);
                throw;
            }
        }
    }

    // Конструктор перемещения
    Stack(Queue&& other, const allocator_type& alloc = {}) noexcept
     : allocator_(std::move(alloc))
     , sz_(other.sz_)
     , cap_(other.sz_)
     , data_(other.data_)
    {
        other.sz_ = 0;
        other.cap_ = 0;
        other.data_ = nullptr;
    }

    // Конструктор от двух итераторов
    template < std::input_iterator InputIt >
    Stack(InputIt first, InputIt last, const allocator_type& alloc = {})
     : Stack(alloc)
    {
        for (auto it = first; it != last; ++it) {
            this->Push(*it);
        }
    }

    // Деструктор
    ~Stack() noexcept {
        while (!this->Empty()) {
            this->Pop();
        }
        this->allocator_.deallocate(this->data_, this->cap_);
    }

    /* Итераторы и доступ к элементам */

    T& Top() const noexcept {
        return this->data_[this->sz_ - 1];
    }

    inline Iterator Begin() const noexcept {
        return Iterator(this->data_ + this->sz_ - 1);
    }

    inline Iterator End() const noexcept {
        return Iterator(this->data_ - 1);
    }

    inline ConstIterator CBegin() const noexcept {
        return ConstIterator(this->data_);
    }

    inline ConstIterator CEnd() const noexcept {
        return ConstIterator(this->data_ + this->sz_);
    }

    /* Размер и капасити */

    bool Empty() const noexcept {
        return this->sz_ == 0;
    }

    size_t Size() const noexcept {
        return this->sz_;
    }

private:
    void CheckCapacity() {
        if (this->sz_ >= this->cap_) {
            this->Reserve(std::max(MIN_CAP, 2 * this->cap_));
        }
    }
public:
    void Reserve(size_t new_cap) {
        if (new_cap <= this->cap_) {
            return;
        }

        // выделяем память для нового массива
        T* new_data = this->allocator_.allocate(new_cap);

        // переносим элементы и отслеживаем исключения (чтобы почистить память)
        for (size_t i = 0; i < this->sz_; ++i) {
            try {
                this->allocator_.construct(new_data + i, std::move_if_noexcept(this->data_[i]));
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    allocator_traits::destroy(this->allocator_, new_data + j);
                }
                this->allocator_.deallocate(new_data, new_cap);
                throw;
            }
        }
        for (size_t i = 0; i < this->sz_; ++i) {
            allocator_traits::destroy(this->allocator_, this->data_ + i);
        }
        this->allocator_.deallocate(this->data_, this->cap_);

        this->cap_ = new_cap;
        this->data_ = new_data;
    }

    /* Изменение стека */ 

    void Push(const T& value) {
        this->CheckCapacity();
        this->allocator_.construct(this->data_ + this->sz_, value);
        ++this->sz_;
    }

    void Push(T&& value) noexcept {
        this->CheckCapacity();
        this->allocator_.construct(this->data_ + this->sz_, std::move(value));
        ++this->sz_;
    }

    template< class... Args >
    void Emplace(Args&&... args) {
        this->CheckCapacity();
        this->allocator_.construct(this->data_ + this->sz_, std::forward<Args>(args)...);
        ++this->sz_;
    }

    void Pop() noexcept {
        --this->sz_;
        allocator_traits::destroy(this->allocator_, this->data_ + this->sz_);
    }
};
