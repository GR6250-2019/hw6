// fms_cumulant_poisson.h - Poisson cumulant
#pragma once
#include <cmath>

namespace fms::cumulant {

    // Cumulants of a Poisson random variable: lambda, lambda, ....
    template<class S = double>
    class Poisson {
        S lambda;
    public:
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
        // Poisson cumulant.
        //   E exp(sX) = sum_{k>=0} exp(sk) lambda^k/k!/exp(lambda) =
        //             = sum_{k>=0} (e^s lambda)^k/k!/exp(lambda))
        //             = exp(e^s lambda))/exp(lambda)
        //             = exp(e^s lambda - lambda)
        S operator()(const S& s) const
        {
            return lambda * (exp(s) - 1);
        }
    };
    // kappa^*_n = sum_{k>=0} lambda * s^k/k! = lambda exp(s)
    template<class S = double>
    inline auto shift(Poisson<S> ks, const S& s)
    {
        return Poisson(*ks * exp(s));
    }
}
