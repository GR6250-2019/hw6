// fms_probability_poisson.h - Poisson distributiong
//  P(X = k) = exp(-lambda) lambda^k/k!
#pragma once
#include <cmath>

namespace fms::probability {

    template<class X = double>
    class Poisson {
        X lambda;
    public:
        Poisson(X lambda)
            : lambda(lambda)
        { }
        X pdf(X k) const
        {
            X k_;
            if (k < 0 || 0 != modf(k, &k_)) {
                return X(0);
            }
            X l_k = 1; // lambda^k/k!
            for (X j = 1; j <= k; ++j) {
                l_k *= lambda / j;
            }

            return exp(-lambda) * l_k;
        }
        X cdf(X x) const
        {
            if (x < 0) {
                return X(0);
            }
            X l_k = 1; // lambda^k/k!
            X p = l_k;
            for (X j = 1; j <= x; ++j) {
                l_k *= lambda / j;
                p += l_k;
            }

            return exp(-lambda) * p;
        }
        X cumulant(X s) const
        {
            return lambda * (exp(s) - 1);
        }
        X cumulants(size_t n) const
        {
            return n == 0 ? X(0) : lambda;
        }
    };
}
