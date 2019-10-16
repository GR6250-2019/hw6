// fms_cumulant_poisson.t.cpp - Test Poisson cumulant.
#include <cassert>
#include <limits>
#include "fms_cumulant.h"
#include "fms_cumulant_poisson.h"

using namespace fms::cumulant;

template<class S>
int test_cumulant_poisson()
{
    S lambda = 0.5;
    Poisson<> kappa(lambda);
    assert(kappa(0.25) == lambda * (exp(0.25) - 1));
    assert(kappa);
    assert(*kappa == lambda);
    assert(*++kappa == lambda);
    assert(*++kappa == lambda);
    assert(*++kappa == lambda);

    double s = 0.1;
    auto kappa_ = shift(kappa, s);
    assert(*kappa_ == lambda * exp(s));
    for (double u : {-1., 0., 1.}) {
        double ku_ = kappa_(u);
        double ku = kappa(u + s) - kappa(s);
        double dku = ku_ - ku;
        assert(fabs(dku) <= std::numeric_limits<double>::epsilon());
    }

    return 0;
}

int test_cumulant_poisson_double = test_cumulant_poisson<double>();