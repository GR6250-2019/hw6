// fms_probability_normal.h
// Density function phi(x) = exp(-x^2/2)/sqrt(2 pi)
#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <utility>

#ifndef M_SQRT2PI
#define M_SQRT2PI  2.50662827463100050240
#endif

namespace fms::probability {

    template<class X = double>
    class Normal {
        X mu, sigma;
    public:
        Normal(X mu, X sigma)
            : mu(mu), sigma(sigma)
        { }
        // Normal probability density function.
        X pdf(X x)
        {
            auto z = (x - mu) / sigma;

            return exp(-z * z / 2) / (sigma * M_SQRT2PI);
        }
        // Normal cumulative distribution function.
        X cdf(X x)
        {
            auto z = (x - mu) / sigma;

            return (1 + erf(z / M_SQRT2)) / 2;
        }
        X cumulant(X s) const
        {
            return mu * s + sigma * sigma * s * s/2;
        }
        size_t cumulants(size_t n) const
        {
            return n == 1 ? mu : n == 2 ? sigma * sigma : 0;
        }
    };
}
