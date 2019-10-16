// fms_Hypergeometic.h - Hypergeometric function F(a,b;c;x) = sum_{n>=0} (a)_n (b)_n/(c)_n x^n/n!
#pragma once
#include <tuple>
#include "fms_sequence.h"

namespace fms {

    template<class X = double>
    inline std::tuple<X,size_t> Hypergeometric(const X& a, const X& b, const X& c, const X& x, long n = 100)
    {
        using fms::sequence::sum;
        using fms::sequence::epsilon;
        using fms::sequence::take;
        using fms::sequence::factorial;
        using fms::sequence::power;
        using fms::sequence::length;

        auto series = epsilon(factorial(a) * factorial(b) * power(x) / (factorial(c) * factorial(X(0))));

        return std::tuple(sum(take(n,series)), length(take(n,series)));
    }

}
