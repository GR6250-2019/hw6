// fms_cumulant_poisson.h - Poisson cumulant
#pragma once
#include <cmath>

namespace fms::cumulant {

    // Cumulants of a Poisson random variable times a scalar c: c*lambda, c^2*lambda, ....
    template<class S = double>
    class Poisson {
        S lambda;
        S c; // scale
        S cn; // c^n
    public:
        Poisson(S lambda = 0, S c = S(1))
            : lambda(lambda), c(c), cn(c)
        { }

        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return cn*lambda;
        }
        Poisson& operator++()
        {
            cn *= c;

            return *this;
        }
        // Poisson cumulant.
        S operator()(const S& s) const
        {
            return lambda * (exp(c*s) - 1);
        }
        // Poisson under the measure dP_/dP = exp(s X - kappa(s))
        Poisson _(const S& s) const
        {
            return Poisson(exp(s) * lambda, c);
        }
    };
}
