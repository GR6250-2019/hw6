// fms_sequence_epsilon.h - terminate at machine epsilon
#pragma once
#include <compare>
#include <type_traits>

namespace fms::sequence {

    // machine epsilon terminated sequence
    template<class S>
    class epsilon {
        S s;
        using X = decltype(*s);
        X one;
    public:
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