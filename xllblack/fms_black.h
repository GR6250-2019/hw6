// fms_black.h - Black model
#pragma once
#include <algorithm>
#include "..//xll12/xll/ensure.h"
#include "fms_normal.h"

namespace fms::black {

	// F = f exp(sigma B_t - sigma^2 t/2) is the Black model.
	// F <= k if and only if B_t/sqrt(t) <= (sigma^2 t/2 + log (k/f))/sigma sqrt(t)
	template<class F, class S, class K>
	inline auto moneyness(F f, S s, K k)
	{
		ensure(f > 0);
		ensure(s > 0);
		ensure(k > 0);

		return (s * s / 2 + log(k / f)) / s;
	}

    // E(k - F)^+ = k P(F <= k) - f P_(F <= k)
	template<class F, class S, class K, class T>
	inline auto put(F f, S sigma, K k, T t)
	{
        ensure(sigma > 0);
        ensure(t > 0);

        auto s = sigma * sqrt(t);
		auto z = moneyness(f, s, k);
		auto z_ = z - s;

		return k * normal::cdf(z) - f * normal::cdf(z_);
	}

    // E(F - k)^+ = f P_(F >= k) - k P(F >= k)
	template<class F, class S, class K, class T>
	inline auto call(F f, S sigma, K k, T t)
	{
        ensure(sigma > 0);
        ensure(t > 0);
        
        auto s = sigma * sqrt(t);
        auto z = moneyness(f, s, k);
        auto z_ = z - s;

		return f * normal::cdf(-z_) - k * normal::cdf(-z); // 1 - Phi(x) = Phi(-x)
	}

    // Derivative of put value with respect to f.
    template<class F, class S, class K, class T>
    inline auto put_delta(F f, S sigma, K k, T t)
    {
        ensure(sigma > 0);
        ensure(t > 0);
        
        auto s = sigma * sqrt(t);
        auto z = moneyness(f, s, k);
        auto z_ = z - s;

        return -normal::cdf(z_);
    }

    // Derivative of a put or call value with respect to sigma.
    template<class F, class S, class K, class T>
    inline auto vega(F f, S sigma, K k, T t)
    {
        ensure(sigma > 0);
        ensure(t > 0);
        
        auto s = sigma * sqrt(t);
        auto z = moneyness(f, s, k);
        auto z_ = z - s;

        return f*normal::pdf(z_)*s/sigma;
    }

    // Value of sigma for a put having value p.
    template<class F, class P, class K, class T>
    inline auto put_implied_volatility(F f, P p, K k, T t)
    {
        //!!! Put in appropriate checks, including bounds for p.
        ensure(f > 0);
        ensure(k > 0);
        ensure(t > 0);
        ensure(p > 0);
        ensure(p > k - f);

        P sigma_, sigma = 0.2; // initial guess
        do {
            sigma_ = sigma - (put(f, sigma, k, t) - p) / vega(f, sigma, k, t);
            std::swap(sigma_, sigma);
        } while (fabs(sigma_ - sigma) > 100 * std::numeric_limits<double>::epsilon());

        return sigma_; // !!!implement using Newton-Raphson 
    }

} // fms::black