// fms_sequence_iota.h - 0, 1, 2, ...
#pragma once
#include <compare>

namespace fms::sequence {

    template<class X = double>
    class iota {
        X x;
    public:
        iota(X x = 0)
            : x(x)
        { }
        const auto operator<=>(const iota&) const = default;
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return x;
        }
        iota& operator++()
        {
            ++x;

            return *this;
        }
    };

}