//Sample provided by Fabio Galuppo
//May 2015
//http://www.simplycpp.com

#include <iterator>
#include <iostream>
#include <numeric>

namespace write_only
{
    template <class T>
    struct cout_iterator final :
        public std::iterator<std::output_iterator_tag, void, void, void, void>
    {
        cout_iterator() :
            cout_iterator (nullptr, nullptr, nullptr) {}
        
        cout_iterator(const char* separator) :
            cout_iterator (nullptr, separator, nullptr) {}
        
        cout_iterator(const char* begin_separator, const char* separator, const char* end_separator) :
            delim_flag(false),
            end_delim_flag(true),
            delim(separator),
            end_delim(end_separator)
        {
            if (begin_separator)
                std::cout << begin_separator;
        }
        
        //copy-constructible
        cout_iterator(const cout_iterator<T>& other) :
            delim_flag(other.delim_flag),
            end_delim_flag(true),
            delim(other.delim),
            end_delim(other.end_delim)
        {
            const_cast<cout_iterator<T>&>(other).end_delim_flag = false;
        }
        
        //copy-assignable
        cout_iterator<T>& operator=(const cout_iterator<T>& other)
        {
            delim_flag = other.delim_flag;
            end_delim_flag = true;
            delim = other.delim;
            end_delim = other.end_delim;
            const_cast<cout_iterator<T>&>(other).end_delim_flag = false;
            return *this;
        }
        
        //destructible
        ~cout_iterator()
        {
            if (end_delim_flag && end_delim)
                std::cout << end_delim;
        }
        
        //assignable
        cout_iterator<T>& operator= (const T& val)
        {
            if (delim_flag) { if (delim) std::cout << delim; }
            else { delim_flag = true; }
            
            std::cout << val;
            return *this;
        }
        
        //dereference
        cout_iterator<T>& operator*() { return *this; }
        
        //pre increment
        cout_iterator<T>& operator++() { return *this; }
        
        //post increment
        cout_iterator<T>& operator++(int) { return *this; }
        
    private:
        bool delim_flag, end_delim_flag;
        const char *delim, *end_delim;
    };
    
    template <class InputIterator, class OutputIterator>
    void write_range(InputIterator first, InputIterator last, OutputIterator& result)
    {
        while (first != last)
        {
            *result = *first;
            ++result;
            ++first;
        }
    }
}

int run_main()
{
    int xs[10];
    std::iota(xs, xs + 10, 1); //[xs, xs + 10) as Forward Iterator
    { //begin scope
        write_only::cout_iterator<int> ys {"{", " ", "}\n"}; //Output Iterator
        write_only::write_range(xs, xs + 10, ys); //[xs, xs + 10) as Input Iterator; ys as Output Iterator
        write_only::cout_iterator<int> zs = ys, ws;
        zs = ys;
        ++zs;
        zs++;
        *zs = 11;
        ws = zs;
        *ws = 12;
        *ys = 13; *zs = 14; *ws = 15;
    } //end scope
    std::cout << "An odd sample for OutputIterator :-)\n";
    //more info about OutputIterator: http://www.cplusplus.com/reference/iterator/OutputIterator/
    
    return 0;
}
