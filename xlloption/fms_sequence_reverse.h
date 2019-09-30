// fms_sequence_reverse.h - reverse sequence if it has operator--()
#pragma once
#include <compare>

namespace fms::sequence {

    template<class S>
    class reverse {
        S s;
    public:
        // Constructor should be the last element of the sequence, not one past the end.
        reverse(S s)
            : s(s)
        { }
        const auto operator<=>(const reverse&) const = default;
        operator bool() const
        {
            return true; //!!! unchecked
        }
        auto operator*() const
        {
            return *s;
        }
        reverse& operator++()
        {
            --s;

            return *this;
        }
    };

}
