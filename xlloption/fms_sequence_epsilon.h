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
    public:
        epsilon(S s)
            : s(s)
        { }
        const auto operator<=>(const epsilon&) const = default;
        operator bool() const
        {
            return *s + X(1) != X(1);
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