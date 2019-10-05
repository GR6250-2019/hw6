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
        X sigma = sqrt(variance);
        ++kappa;

        auto kappa3 = scale(1 / sigma, kappa) / sequence::constant(variance);

        return std::tuple(mean, sigma, kappa3);
    }

    template<class S = double>
    struct normal {
        static S cumulant(S s)
        {
            return s * s / 2;
        }
        // 0, 1, 0, ...
        class cumulants {
            size_t n;
        public:
            cumulants()
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
            cumulants& operator++()
            {
                ++n;

                return *this;
            }
        };
    };

    template<class S = double>
    class Poisson {
        S lambda;
    public:
        Poisson(S lambda = 0)
            : lambda(lambda)
        { }

        S cumulant(S s)
        {
            return lambda*(exp(s) - 1);
        }
        static S cumulant(S s, S lambda_)
        {
            return lambda_ * (exp(s) - 1);
        }
        // lambda, lambda, ....
        class cumulants {
            S lambda;
        public:
            cumulants(S lambda = 0)
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
            cumulants& operator++()
            {
                return *this;
            }
        };

    };

}
