// fms_sequence_pair.h - Return pairs from two sequences. 
#pragma once
#include <tuple>

namespace fms::sequence {

    template<class S, class T>
    class pair {
        S s;
        T t;
    public:
        pair(const S& s, const T& t)
            : s(s), t(t)
        { }
        // <=>
        operator bool() const
        {
            return s && t;
        }
        auto operator*() const
        {
            return std::pair{ *s, *t };
        }
        pair& operator++()
        {
            ++s;
            ++t;

            return *this;
        }
    };

}
