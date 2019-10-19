// fms_sequence_pair.h - Return pairs from two sequences. 
#pragma once
#include <tuple>
#include "fms_sequence_traits.h"
#include "fms_sequence_list.h"

namespace fms::sequence {

    template<class S, class T, class X = common_value_type<S,T>>
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
            return list<X>({ *s, *t });
        }
        pair& operator++()
        {
            ++s;
            ++t;

            return *this;
        }
    };

}
