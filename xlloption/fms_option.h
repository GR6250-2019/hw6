// fms_option.h - General option pricing.
// See https://github.com/keithalewis/papers/blob/master/options.pdf
// F = f exp(sX - kappa(s)) where X has mean 0 variance 1.
// Note E[F] = f and Var(log(F)) = s^2.
// F <= k iff X <= (kappa(s) + log k/f)/s
#pragma once
#include <algorithm>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <tuple>
#include "fms_probability_normal.h"
#include "fms_Bell.h"
#include "fms_Hermite.h"
#include "fms_sequence.h"
#include "fms_cumulant.h"

namespace fms::option {

    // F <= k iff X <= z where F = f exp(sX - kappa(s)) and z = (kappa(s) + log(k/f))/s
    template<class F, class S, class K, class Kappa = std::function<S(S)>>
    inline auto moneyness(F f, S s, K k, const Kappa& kappa)
    {
        auto scale = std::max(f, std::max(s, k));
        using Z = decltype(f + s + k);
        constexpr auto infinity = std::numeric_limits<Z>::infinity();

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

    // Probability density function of X where X has cumulants kappa.
    //
    //   phi(x) sum_{n} bell_n(0,0,kappa_3,...,kappa_n) Hermite_n(x) if X has mean 0, variance 1.
    //
    // Normalize to X' = (X - mu)/sigma and X == x iff X' == (x - mu)/sigma.
    template<class X, class K>
    inline auto pdf(X x, K kappa)
    {
        using fms::sequence::concatenate;
        using fms::sequence::epsilon;
        using fms::sequence::list;
        using fms::sequence::sum;
        using fms::sequence::take;

        auto [mu, sigma, kappa3] = cumulant::normalize(kappa);
        auto x_ = (x - mu) / sigma;

        bell b(concatenate(list({ 0, 0 }), kappa3));
        Hermite H(x_);
        X phi = fms::probability::Normal<X>().pdf(x_);

        return phi*sum(take(100, epsilon(b * H, phi, 6)))/sigma;
    }
    
    // Probability X <= x where X has cumulants kappa.
    //   Phi(x) - phi(x) sum_{n>=3} bell_n(0,0,kappa_3,...,kappa_n) Hermite_{n-1}(x) if X has mean 0, variance 1.
    // Normalize to X' = (X - mu)/sigma and X <= x iff X' <= (x - mu)/sigma.
    template<class X, class K>
    inline auto cdf(X x, K kappa)
    {
        using fms::sequence::concatenate;
        using fms::sequence::constant;
        using fms::sequence::epsilon;
        using fms::sequence::list;
        using fms::sequence::skip;
        using fms::sequence::sum;
        using fms::sequence::take;

        auto [mu, sigma, kappa3] = cumulant::normalize(kappa);
        auto x_ = (x - mu) / sigma;

        bell b(concatenate(list({ 0, 0 }), kappa3));
        auto b3 = skip(3, b); // bell_n(0, 0, kappa_3, ..., kappa_n)

        Hermite H(x_);
        auto H2 = skip(2, H); // Hermite_{n-1}(x)
        
        fms::probability::Normal<X> N;
        X phi = N.pdf(x_);

        return N.cdf(x_) - phi*sum(take(100, epsilon(b3 * H2, phi, 3)));
    }

    // E(k - F)^+ = k P(F <= k) - f P_(F <= k)
    // where dP_/dP = exp(s X - kappa(s))
    template<class F, class S, class K, class Kappa>
    inline auto put(F f, S s, K k, Kappa kappa)
    {
        auto z = moneyness(f, s, k, kappa);
        auto kappa_ = fms::cumulant::shift(kappa, s);
       
        return k * cdf(z, kappa) - f * cdf(z, kappa_);
    }

    // E(F - k)^+ = f P_(F >= k) - k P(F >= k)
    // where dP_/dP = exp(s X - kappa(s))
    template<class F, class S, class K, class Kappa>
    inline auto call(F f, S s, K k, Kappa kappa)
    {
        auto z = moneyness(f, s, k, kappa);
        auto kappa_ = fms::cumulant::shift(kappa, s);

        return f * (1 - cdf(z, kappa_)) - k * (1 - cdf(z, kappa));
    }

} // fms::option
