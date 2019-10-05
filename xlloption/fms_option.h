// fms_option.h - General option pricing.
// F = f exp(sX - kappa(s))
// F <= k iff X <= (kappa(s) + log k/f)/s
#pragma once
#include <functional>
#include <tuple>
#include "fms_normal.h"
#include "fms_Bell.h"
#include "fms_Hermite.h"
#include "fms_sequence.h"
#include "fms_cumulant.h"

namespace fms::option {

    template<class F, class S, class K, class Kappa = std::function<S(S)>>
    inline auto moneyness(F f, S s, K k, const Kappa& kappa)
    {
        //!!! check 
        return (kappa(s) + log(k / f)) / s;
    }

    // Phi(x) - phi(x) sum_{n>3} b_n(0,0,kappa_3,...,kappa_n) H_{n-1}(x)
    template<class X, class Kappas>
    inline auto cdf(X x, Kappas kappa)
    {
        using fms::sequence::concatenate;
        using fms::sequence::constant;
        using fms::sequence::epsilon;
        using fms::sequence::list;
        using fms::sequence::skip;
        using fms::sequence::sum;

        auto [mu, sigma, kappa3] = cumulant::normalize(kappa);
        auto x_ = (x - mu) / sigma;

        Hermite H(x_);
        auto H2 = skip(2, H);
        bell b(concatenate(list({ 0, 0 }), kappa3)); // reduced Bell polynomial
        auto b3 = skip(3, b);

        auto s = sum(epsilon(constant(normal::pdf(x_)) * b3 * H2));

        return normal::cdf(x_) - s;
    }

} // fms::option
