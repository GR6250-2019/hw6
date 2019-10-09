// fms_sequence_take.h - iterators with operator bool() const
#pragma once
#include <compare>
#include "fms_sequence_reverse.h"

namespace fms::sequence {

    template<class S>
    class take {
        long n;
        S s;
    public:
        take(long n, S s)
            : n(n), s(s)
        {
            if (n < 0) {
                n = -n;
                // constexpr if has reverse
                //s = take(n, reverse(s, s - n));
            }
        }
        const auto operator<=>(const take&) const = default;
        operator bool() const
        {
            return n != 0 && s;
        }
        auto operator*() const
        {
            return *s;
        }
        take& operator++()
        {
            if (operator bool()) {
                --n;
                ++s;
            }

            return *this;
        }
    };

}
