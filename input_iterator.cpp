//Sample provided by Fabio Galuppo
//June 2015
//http://www.simplycpp.com

#include <iterator>
#include <iostream>

template <class T>
struct increment_t final
{
    void operator()(T& x) const { ++x; }
};

template <class T>
struct decrement_t final
{
    void operator()(T& x) const { --x; }
};

namespace read_only
{
    template <class T, class Successor = increment_t<T>>
    struct generator_iterator final :
        public std::iterator<std::input_iterator_tag, T, void, const T*, const T&>
    {
        //default-constructible
        generator_iterator() : state(T{}), next(Successor{}) {}
        
        generator_iterator(const T& init) : state(init), next(Successor{}) {}
        
        //copy-constructible
        generator_iterator(const generator_iterator& other) :
            state(other.state), next(other.next) {}
        
        //copy-assignable
        generator_iterator& operator=(const generator_iterator& other)
        {
            state = other.state;
            next = other.next;
            return *this;
        }
        
        //destructible
        ~generator_iterator() = default;
        
        //dereference
        const T& operator*() const { return state; }
        
        //dereference
        const T* operator->() const { return &(operator*()); }
        
        //pre increment
        generator_iterator& operator++()
        {
            next(state);
            return *this;
        }
        
        //post increment
        generator_iterator operator++(int)
        {
            generator_iterator temp(*this);
            ++(*this);
            return temp;
        }
        
        //equality
        friend
        bool operator==(const generator_iterator& lhs, const generator_iterator& rhs)
        {
            return lhs.state == rhs.state;
        }
        
        //inequality
        friend
        bool operator!=(const generator_iterator& lhs, const generator_iterator& rhs)
        {
            return !(lhs == rhs);
        }
        
    private:
        T state;
        Successor next;
    };
}

template <class InputIterator>
void print_it(InputIterator& it, int tabs)
{
    for (int i = 0; i < tabs; ++i)
        std::cout << "\t";
    std::cout << *it << "\n";
}

template <class InputIterator>
void print_range(InputIterator& it, const InputIterator& it_end)
{
    while (it != it_end)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "\n";
}

int main()
{
    read_only::generator_iterator<int> gi1;
    print_it(gi1, 0); ++gi1;
    print_it(gi1, 0); ++gi1;
    auto gi2 = gi1++;
    print_it(gi2, 1); ++gi2;
    print_it(gi1, 0); ++gi1;
    print_it(gi1, 0); ++gi1;
    print_it(gi2, 1); ++gi2;
    
    read_only::generator_iterator<int> gi3;
    gi3 = gi2;
    print_it(gi3, 2); ++gi3;
    print_it(gi3, 2);
    
    read_only::generator_iterator<int> it, end_it(10);
    print_range(it, end_it);
    
    read_only::generator_iterator<int, decrement_t<int>> jt, end_jt(-10);
    print_range(jt, end_jt);

    auto increment_by_2 = [](int& x){ x += 2; };
    read_only::generator_iterator<int, decltype(increment_by_2)> kt,
        end_kt(10); //take care with increments that bypass end_kt
    print_range(kt, end_kt);
    
    read_only::generator_iterator<int> lt(5), end_lt(10);
    print_range(lt, end_lt);
    
    read_only::generator_iterator<int, decltype(increment_by_2)> mt(5),
        end_mt(11);
    print_range(mt, end_mt);
    
    //more info about InputIterator: http://www.cplusplus.com/reference/iterator/InputIterator/
    
    return 0;
}
