// fms_probability_normal.h
// Density function phi(x) = exp(-x^2/2)/sqrt(2 pi)
#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <compare>
#include <utility>

#ifndef M_SQRT2PI
#define M_SQRT2PI  2.50662827463100050240
#endif

namespace fms::probability {

    template<class X = double>
    class Normal {
        X mu, sigma;
    public:
        Normal(const X& mu = 0, const X& sigma = 1)
            : mu(mu), sigma(sigma)
        { }
		const auto operator<=>(const Normal&) const = default;
        // Normal probability density function.
        X pdf(const X& x) const
        {
            auto z = (x - mu) / sigma;

            return exp(-z * z / 2) / (sigma * X(M_SQRT2PI));
        }
        // Normal cumulative distribution function.
        X cdf(const X& x) const
        {
            auto z = (x - mu) / sigma;

            return (1 + erf(z / X(M_SQRT2))) / 2;
        }
		// Moment generating function: E exp(t X)
		X moment(const X& t) const
		{
			return exp(cumulant(t));
		}
		class moments {
			friend class Normal;
			Normal<X> N;
			X n;
		public:
			moments(const Normal<X>& N)
				: N(N), n(0)
			{ }
			operator bool() const
			{
				return true;
			}
			// E X^n = exp(n mu + n^2 sigma^2/2)
			X operator*() const
			{
				return exp(n * N.mu + n * n * N.sigma * N.sigma / 2);
			}
			moments& operator++()
			{
				++n;

				return *this;
			}
            X operator()(const X& t) const
            {
                return N.moment(t);
            }
        };
        X cumulant(const X& s) const
        {
            return mu * s + sigma * sigma * s * s/2;
        }
		class cumulants {
			friend class Normal;
			Normal<X> N;
			size_t n;
		public:
			cumulants(const Normal<X>& N)
				: N(N), n(0)
			{ }
			operator bool() const
			{
				return true;
			}
			X operator*() const
			{
				return n == 0 ? N.mu : n == 1 ? N.sigma * N.sigma : 0;
			}
			cumulants& operator++()
			{
				++n;

				return *this;
			}
            X operator()(const X& s) const
            {
                return N.cumulant(s);
            }
		};
     };
}
