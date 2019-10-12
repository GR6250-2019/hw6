// fms_sequence_list.h - sequence from initializer list
#pragma once
#include <initializer_list>
#include <vector>

namespace fms::sequence {

    template<class X>
    class list {
        std::vector<X> s;
        size_t n;
    public:
        list(const std::initializer_list<X>& s)
            : s(s.begin(), s.end()), n(0)
        { }
        list(const std::vector<X>& s)
            : s(s), n(0)
        { }
        list(size_t n, const X* s)
            : s(s, s + n), n(0)
        { }
        size_t size() const
        {
            return s.size();
        }
        auto begin()
        {
            return s.begin();
        }
        auto end()
        {
            return s.end();
        }
        void reset()
        {
            n = 0;
        }
        operator bool() const
        {
            return n < s.size();
        }
        X operator*() const
        {
            return s[n];
        }
        X& operator*()
        {
            return s[n];
        }
        list& operator++()
        {
            if (n < s.size()) {
                ++n;
            }

            return *this;
        }
        list& operator--()
        {
            if (n > 0) {
                --n;
            }

            return *this;
        }
    };

}