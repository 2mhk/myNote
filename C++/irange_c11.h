#ifndef __H_IRANGE_C11_H__
#define __H_IRANGE_C11_H__

namespace irange_c11 {
    class irange
    {        //    for (auto i : irange_c11::irange(0, 10)) { std::cout << i << " "; }    //0 1 2 3 4 5 6 7 8 9
    public:
        class iterator {
        public:
            explicit iterator(long val) : value_(val) {}
            bool operator != (const iterator& other) const { return value_ != other.value_; }
            long& operator*() { return value_; }
            const long& operator*() const { return value_; }
            iterator& operator++ () { ++value_; return *this; }
            iterator operator++ (int) { iterator tmp = *this; ++value_; return tmp; }
        private:
            long value_;
        };
        irange(long begin, long end) : m_begin_value(begin), m_end_value(end) {}
        irange(long end) : m_begin_value(0), m_end_value(end) {}
        ~irange() {}
        iterator begin() const { return iterator(m_begin_value); }
        iterator end() const { return iterator(m_end_value); }
    private:
        long m_begin_value;
        long m_end_value;
    };
}



#endif
