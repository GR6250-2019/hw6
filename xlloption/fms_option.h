// fms_option.h - General option pricing.
// F = f exp(sX - kappa(s))
// F <= k iff X <= (kappa(s) + log k/f)/s
#pragma once
#include <functional>
#include "fms_normal.h"
#include "fms_Bell.h"
#include "fms_Hermite.h"
#include "fms_sequence.h"

namespace fms::option {

    template<class F, class S, class K, class Kappa = std::function<S(S)>>
    inline auto moneyness(F f, S s, K k, const Kappa& kappa)
    {
        //!!! check 
        return (kappa(s) + log(k / f)) / s;
    }

    // Phi(x) - phi(x) sum_{n>3} B_n(0,0,kappa_3,...,kappa_n) H_{n-1}(x)/n!
    template<class X, class Kappas>
    inline auto cdf(X x, Kappas kappa)
    {
        using fms::sequence::epsilon;
        using fms::sequence::skip;
        using fms::sequence::sum;

        Hermite H(x);
        bell b(kappa); // reduced Bell polynomial

        auto s = sum(epsilon(skip(3, b) * skip(2, H)));

        return normal::cdf(x) - normal::pdf(x) * s;
    }

} // fms::option
