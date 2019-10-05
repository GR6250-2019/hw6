// fms_sequence_epsilon.h - terminate at machine epsilon
#pragma once
#include <compare>
#include "fms_sequence_traits.h"

namespace fms::sequence {

    // machine epsilon terminated sequence
    template<class S, class X = value_type<S>>
    class epsilon {
        S s;
        X one;
    public:
        // one should be the average size of the values
        epsilon(S s, X one = 1)
            : s(s), one(one)
        { }
        const auto operator<=>(const epsilon&) const = default;
        operator bool() const
        {
            return *s + one != one;
        }
        auto operator*() const
        {
            return *s;
        }
        epsilon& operator++()
        {
            ++s;

            return *this;
        }
    };

}