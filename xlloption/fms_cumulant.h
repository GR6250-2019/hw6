// fms_cumulant.h - A cumulant is a sequence of cumulants, operator() for the cumulant
// and _() for the sequence of cumulants
#pragma once
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <valarray>
#include "fms_sequence.h"
#include "fms_cumulant_constant.h"
#include "fms_cumulant_normal.h"
#include "fms_cumulant_poisson.h"

namespace fms::cumulant {

    // K is cumulant sequence
    template<class K>
    using value_type = std::invoke_result_t<decltype(&K::operator*), K>;

    // Cumulants under the measure P_ with dP_/dP = exp(s X - kappa(s))
    template<class K, class S = value_type<K>>
    class __ { //??? Dumb name, but _ can't be used.
        K k;
        S s;
    public:
        __(K k, S s)
            : k(k), s(s)
        { }
        operator bool() const
        {
            return true; // Assumes all cumulants exist.
        }
        // kappa^{X_}_n = sum_{k >= 0} kappa_{n + k} s^k/k!
        S operator*() const
        {
            using fms::sequence::sum;
            using fms::sequence::epsilon;
            using fms::sequence::power;
            using fms::sequence::factorial;

            return sum(epsilon(k * power(s) / factorial<S>{}));
        }
        __& operator++()
        {
            ++k;

            return *this;
        }
        S operator()(S u)
        {
            return k(u + s) - k(s);
        }
        __ _(S u)
        {
            return __(k, u + s);
        }
    };

    // Cumulants of a scalar multiple of a random variable.
    // kappa^{cX}_n = c^n kappa^X_n
    template<class K, class S = value_type<K>>
    class scale {
        K k;
        S c;
        S cn; // c^n
    public:
        scale(S c, K k)
            : k(k), c(c), cn(c)
        { }
        operator bool() const
        {
            return k;
        }
        S operator*() const
        {
            return cn * (*k);
        }
        scale& operator++()
        {
            ++k;
            cn *= c;

            return *this;
        }
        // kappa^{cX}(s) = kappa(cs)
        S operator()(S s) const
        {
            return k(c * s);
        }
        // kappa^{cX}_n = c^n (kappa_n sum_{k >= 0} kappa_{n + k} s^k/k!)
        auto _(S s) const
        {
            return __(*this, s);
        }
    };

    // Convert to mean 0, variance 1: X' = (X - mu)/sigma
    // kappa'_1 = kappa_1 - mu = 0, kappa'_2 = kappa_2/sigma^2 = 1, kappa_n' = kappa_n/sigma^n for n > 2.
    // Return original mean, standard, deviation, and normalized kappa_n, n >= 3.
    template<class K, class S = value_type<K>>
    inline auto normalize(K kappa)
    {
        S mean = *kappa;
        ++kappa;
        S variance = *kappa;
        ++kappa;

        S sigma = sqrt(variance);
        auto kappa3 = scale(1 / sigma, kappa) / sequence::constant(variance);

        return std::tuple(mean, sigma, std::move(kappa3));
    }

}
