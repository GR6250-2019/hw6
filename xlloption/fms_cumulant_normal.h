// fms_cumulant_normal.h - Normal cumulant
#pragma once

namespace fms::cumulant {

    // Cumulants of a normal random variable: c*mu, c^2*sigma^2, 0, ...
    template<class S = double>
    class Normal {
        S mu;
        S sigma;
        S c;
        size_t n;
    public:
        Normal(S mu = 0, S sigma = 1, S c = 1)
            : mu(mu), sigma(sigma), c(c), n(0)
        { }
        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return n == 0 ? c*mu : n == 1 ? c * c * sigma * sigma : 0;
        }
        Normal& operator++()
        {
            ++n;

            return *this;
        }
        // Normal cumulant
        S operator()(const S& s) const
        {
            return mu * c * s + sigma * sigma * c * c * s * s / 2;
        }
        // Normal under the measure dP_/dP = exp(s X - kappa(s))
        Normal _(S s) const
        {
            return Normal(mu + s, sigma, c);
        }
    };

}