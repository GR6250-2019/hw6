// fms_sequence_take.h - iterators with operator bool() const
#pragma once
#include <compare>

namespace fms::sequence {

    template<class S>
    class take {
        size_t n;
        S s;
    public:
        take(size_t n, S s)
            : n(n), s(s)
        { }
        const auto operator<=>(const take&) const = default;
        operator bool() const
        {
            return n != 0;
        }
        auto operator*() const
        {
            return *s;
        }
        take& operator++()
        {
            if (n != 0) {
                --n;
                ++s;
            }

            return *this;
        }
    };

}
