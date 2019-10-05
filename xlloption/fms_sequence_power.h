// fms_sequence_power.h - 1, x, x ^ 2, ...
#pragma once
#include <compare>

namespace fms::sequence {

    template<class X = double>
    class power {
        X x, xn; // x, x^n
    public:
        power(X x, X xn = 1)
            : x(x), xn(xn)
        { }
        const auto operator<=>(const power&) const = default;
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return xn;
        }
        power& operator++()
        {
            xn *= x;

            return *this;
        }

    };
}