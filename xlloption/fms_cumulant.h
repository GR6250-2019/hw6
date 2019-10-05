// fms_cumulant.h - Cumlant and cumulants
#pragma once
#include <cmath>
#include <tuple>
#include "fms_sequence.h"

namespace fms::cumulant {

    // Cumulants of a scalar multiple of a random variable.
    template<class S>
    class scale {
        S s;
        using X = decltype(*s);
        X c, cn; // c^n
    public:
        scale(X c, S s)
            : s(s), c(c), cn(c)
        { }
        operator bool() const
        {
            return s;
        }
        X operator*() const
        {
            return cn * (*s);
        }
        scale& operator++()
        {
            cn *= c;

            return *this;
        }
    };

    // Convert to mean 0, variance 1: X -> X' = (X - mu)/sigma
    // kappa'_1 = kappa_1 - mu, kappa_n' = kappa_n/sigma^n for n > 1.
    // Return original mean, standard, deviation, and normalized kappa_n, n >= 3.
    template<class Kappa>
    inline auto normalize(Kappa kappa)
    {
        using X = decltype(*kappa);

        X mean = *kappa;
        ++kappa;
        X variance = *kappa;
        ++kappa;

        X sigma = sqrt(variance);
        auto kappa3 = scale(1 / sigma, kappa) / sequence::constant(variance);

        return std::tuple(mean, sigma, kappa3);
    }

    // Linear combination of cumulants
    template<class ...Kappas>
    class sum_product {
        std::tuple<Kappas...> kappas;
        //using X = std::common_type_t<decltype *ss>
    public:
        sum_product()
        { }
    };

    // 0, 1, 0, ...
    template<class S = double>
    class normal {
        size_t n;
    public:
        S operator()(S s)
        {
            return s * s / 2;
        }
        normal()
            : n(0)
        { }
        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return S(n == 1);
        }
        normal& operator++()
        {
            ++n;

            return *this;
        }
    };

    // lambda, lambda, ....
    template<class S = double>
    class Poisson {
        S lambda;
    public:
        S operator()(S s)
        {
            return lambda * (exp(s) - 1);
        }
        Poisson(S lambda = 0)
            : lambda(lambda)
        { }

        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return lambda;
        }
        Poisson& operator++()
        {
            return *this;
        }
    };

}
