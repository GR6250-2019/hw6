// fms_cumulant_normal.h - Normal cumulant
#pragma once

namespace fms::cumulant {

    // Cumulants of a normal random variable: mu, sigma^2, 0, ...
    template<class S = double>
    class Normal {
        S mu;
        S sigma;
        size_t n;
    public:
        Normal(S mu = 0, S sigma = 1)
            : mu(mu), sigma(sigma), n(0)
        { }
        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return n == 0 ? mu : n == 1 ? sigma * sigma : 0;
        }
        Normal& operator++()
        {
            ++n;

            return *this;
        }
        // Normal cumulant log E exp(s X) = mu s + sigma^2 s^2/2
        S operator()(const S& s) const
        {
            return mu * s + sigma * sigma * s * s / 2;
        }
    };
    // P_(X <= x) = P(X + s <= x)
    template<class S>
    inline auto shift(Normal<S> ks, const S& s)
    {
        S mean = *ks;
        ++ks;
        S variance = *ks;

        return Normal(mean + s, sqrt(variance));
    }

}