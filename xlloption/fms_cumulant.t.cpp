// fms_cumulant.t.cpp - Test cumulant and cumulants
#include <cassert>
#include "fms_sequence.h"
#include "fms_cumulant.h"

using namespace fms::sequence;
using namespace fms::cumulant;

int test_fms_cumulant___()
{
    double lambda = 1;
    double u = 0.1, s = 0.5;
    Poisson p(lambda);
    __ p_(p, s);
    assert(p_(u) == p(u + s) - p(s));
    double exps = exp(s);
    assert(p_);
    assert(fabs(*p_ - exps) <= 2 * std::numeric_limits<double>::epsilon());
    ++p_;
    assert(fabs(*p_ - exps) <= 2 * std::numeric_limits<double>::epsilon());
    ++p;
    assert(fabs(*p_ - exps) <= 2 * std::numeric_limits<double>::epsilon());

    return 0;
}
int test_fms_cumulant____ = test_fms_cumulant___();

int test_fms_cumulant_scale()
{
    double lambda = 1;
    double s = 0.5;
    Poisson p(lambda);

    {
        scale ps(s, p);

        assert(*ps == s * (*p));
        ++ps; ++p;
        assert(*ps == s * s * (*p));
        ++ps; ++p;
        assert(*ps == s * s * s * (*p));
    }
    {
        constexpr double eps = std::numeric_limits<double>::epsilon();
        scale ps(s, p);
        double u = 0.1;
        auto ps_ = ps._(u);
        // s, s^2, s^3, ... ->
        // s 1 + s^2 u + s^3 u^2/2! + ... = s exp(su)
        assert(ps_);
        double ps1_ = s * exp(s * u);
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