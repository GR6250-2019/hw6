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

    // K is the cumulant sequence
    template<class K>
    using value_type = std::invoke_result_t<decltype(&K::operator*), K>;

    // Cumulants under the measure P_ with dP_/dP = exp(s X - kappa(s))
    template<class K, class S = value_type<K>>
    class _ {
        K k;
        S s;
    public:
        _(const K& k, const S& s)
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
            K k2(k);
            auto s2 = *++k2; // variance

            return sum(epsilon(k * power(s) / factorial<S>{}, s2, 2));
        }
        _& operator++()
        {
            ++k;

            return *this;
        }
        S operator()(const S& u) const
        {
            return k(u + s) - k(s);
        }
    };
    template<class K, class S = value_type<K>>
    inline auto shift(const K& k, const S& s)
    {
        return _(k, s);
    }

    // Cumulants of a scalar multiple of a random variable.
    // kappa^{cX}_n = c^n kappa^X_n
    template<class K, class S = value_type<K>>
    class scale {
        K k;
        S c, cn; // c^n
    public:
        scale(const K& k, const S& c, const S& cn = 0)
            : k(k), c(c), cn(cn == 0 ? c : cn)
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
        S operator()(const S& s) const
        {
            return k(c * s);
        }
    };

    // Convert to mean 0, variance 1: X' = (X - mu)/sigma
    // kappa'_1 = kappa_1 - mu = 0, kappa'_2 = kappa_2/sigma^2 = 1, kappa_n' = kappa_n/sigma^n for n > 2.
    // Return original mean, standard deviation, and normalized kappa_n, n >= 3.
    template<class K, class S = value_type<K>>
    inline auto normalize(K kappa)
    {
        S mean = *kappa;
        ++kappa;
        S variance = *kappa;
        ++kappa;
        S sigma = sqrt(variance);

        return std::tuple(mean, sigma, scale(kappa, 1/sigma, 1/variance));
    }

}
