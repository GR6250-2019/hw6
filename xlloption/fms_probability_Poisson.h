// fms_probability_poisson.h - Poisson distributiong
//  P(X = k) = exp(-lambda) lambda^k/k!
#pragma once
#include <cmath>
#include "fms_Touchard.h"

namespace fms::probability {

    template<class X = double>
    class Poisson {
        X lambda;
    public:
        Poisson(const X& lambda)
            : lambda(lambda)
        { }
        X pdf(const X& k) const
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
        X cdf(const X& x) const
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
		// Moment generating function: E exp(tX)
		X moment(const X& t) const
		{
			return exp(cumulant(t));
		}
		class moments {
			friend class Poisson;
			Poisson<X> P;
			Touchard<X> T;
		public:
			moments(const Poisson<X>& P)
				: P(P), T(P.lambda)
			{ }
			operator bool() const
			{
				return true;
			}
			// E X^n = T_n(x) = sum_{k=0}^n {n;k} lambda^k
            // where T_n is the n-th Touchard polynomial
			// and where {n;k} are the Sterling numbers of the second kind.
			X operator*() const
			{
				return *T;
			}
			moments& operator++()
			{
				++T;

				return *this;
			}
            X operator()(const X& t) const
            {
                return P.moment(t);
            }

		};
        X cumulant(const X& s) const
        {
            return lambda * (exp(s) - 1);
        }
		class cumulants {
			friend class Poisson;
			Poisson<X> P;
		public:
			cumulants(const Poisson<X>& P)
				: P(P)
			{ }
			operator bool() const
			{
				return true;
			}
			X operator*() const
			{
				return P.lambda;
			}
			cumulants& operator++()
			{
				return *this;
			}
            X operator()(const X& s) const
            {
                return P.cumulant(s);
            }
		};
        
    };
}
