// fms_option.h - General option pricing.
// F = f exp(sX - kappa(s))
// F <= k iff X <= (kappa(s) + log k/f)/s
#pragma once
#include <algorithm>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <tuple>
#include "fms_normal.h"
#include "fms_Bell.h"
#include "fms_Hermite.h"
#include "fms_sequence.h"
#include "fms_cumulant.h"

namespace fms::option {

    // F <= k iff X <= z where F = f exp(sX - kappa(s)) and z is the moneyness z = (kappa(s) + log(k/f))/s
    template<class F, class S, class K, class Kappa = std::function<S(S)>>
    inline auto moneyness(F f, S s, K k, const Kappa& kappa)
    {
        using Z = decltype((kappa(s) + log(k / f)) / s);
        auto scale = std::max(f, std::max(s, k));
        auto infinity = std::numeric_limits<Z>::infinity();

        if (f < 0) {
            throw std::invalid_argument("fms::option::moneyness: the forward must be non-negative");
        }
        if (k < 0) {
            throw std::invalid_argument("fms::option::moneyness: the strike must be non-negative");
        }
        if (s < 0) {
            throw std::invalid_argument("fms::option::moneyness: the volatility must be non-negative");
        }
        // Edge cases
        if (f + F(scale) == F(scale)) { // f = 0 to machine epsilon
            return infinity;
        }
        if (k + K(scale) == K(scale)) {
            return -infinity;
        }
        if (s + S(scale) == S(scale)) {
            // k/f < 1 -> -infinity
            // k/f > 1 -> ininity
            return copysign(Z(1), k - f) * infinity;
        }
       
        return (kappa(s) + log(k / f)) / s;
    }

    // Probability X <= x where X has cumulants kappa.
    // Phi(x) - phi(x) sum_{n>3} bell_n(0,0,kappa_3,...,kappa_n) Hermite_{n-1}(x) if X has mean 0, variance 1.
    // Normalize to X' = (X - mu)/sigma and X <= x iff X' <= (x - mu)/sigma.
    template<class X, class Kappa>
    inline auto cdf(X x, Kappa kappa)
    {
        using fms::sequence::concatenate;
        using fms::sequence::constant;
        using fms::sequence::epsilon;
        using fms::sequence::list;
        using fms::sequence::skip;
        using fms::sequence::sum;
 
        auto [mu, sigma, kappa3] = cumulant::normalize(kappa);
        auto x_ = (x - mu) / sigma;

        bell b(concatenate(list({ 0, 0 }), kappa3));
        auto b3 = skip(3, b); // bell_n(0, 0, kappa_3, ..., kappa_n)

        Hermite H(x_);
        auto H2 = skip(2, H); // Hermite_{n-1}(x)

        return normal::cdf(x_) - sum(epsilon(constant(normal::pdf(x_)) * b3 * H2));
    }
    /*
    template<class F, class S, class K, class Kappa>
    inline auto put(F f, S s, K k, const Kappa& kappa)
    {
        auto z = moneyness(f, s, k, kappa);
        auto kappa_ = kappa._(s);
       
        return k * cdf(z, kappa) - f * cdf(z, kappa_);
    }
    */
} // fms::option
