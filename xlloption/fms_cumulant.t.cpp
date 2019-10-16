// fms_cumulant.t.cpp - Test cumulant and cumulants
#include <cassert>
#include "fms_sequence.h"
#include "fms_cumulant.h"

using namespace fms::sequence;
using namespace fms::cumulant;

int test_fms_cumulant_shift()
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    double lambda = 1;
    double u = 0.1, s = 0.5;
    Poisson p(lambda);
    auto p_ = shift(p, s);
    // lambda exp(u + s) - lambda exp(s) = lambda exp(s) (exp(u) - 1)
    double pu = p(u + s) - p(s);
    double pu_ = p_(u);
    double dp;
    dp = pu_ - pu;
    assert(fabs(dp) <= 2*eps);
    double exps = exp(s);
    assert(p_);
    assert(fabs(*p_ - lambda*exps) <= 2 * eps);
    ++p_;
    assert(fabs(*p_ - lambda*exps) <= 2 * eps);

    return 0;
}
int test_fms_cumulant_shift_ = test_fms_cumulant_shift();

int test_fms_cumulant_scale()
{
    double lambda = 1;
    double s = 0.5;
    Poisson p(lambda);

    {
        auto ps = scale(p, s);

        assert(*ps == s * (*p));
        ++ps; ++p;
        assert(*ps == s * s * (*p));
        ++ps; ++p;
        assert(*ps == s * s * s * (*p));
    }
    {
        constexpr double eps = std::numeric_limits<double>::epsilon();
        scale ps(p, s);
        double u = 0.1;
        auto ps_ = shift(ps, u);
        // s, s^2, s^3, ... ->
        // s 1 + s^2 u + s^3 u^2/2! + ... = s exp(su)
        assert(ps_);
        double ps1_ = s* exp(s * u);
        assert(fabs(*ps_ - ps1_) <= eps);

        ++ps_;
        // s^2, s^3, ... ->
        // s^2 1 + s^3 u + s^4 u^2/2! + ... = s^2 exp(su)
        ps1_ *= s;
        assert(fabs(*ps_ - ps1_) <= eps);

        ++ps_;
        ps1_ *= s;
        assert(fabs(*ps_ - ps1_) <= eps);
    }

    return 0;
}
int test_fms_cumulant_scale_ = test_fms_cumulant_scale();

int test_cumulant_normalize()
{
    double lambda = 1;
    Poisson p(lambda);
    auto [m, s, kappa] = normalize(p);
    assert(m == *p);
    assert(s * s == *++p);
    assert(*kappa == lambda / (s * s * s));
    assert(*++kappa == lambda / (s * s * s *s));

    return 0;
}
int test_cumulant_normalize_ = test_cumulant_normalize();
