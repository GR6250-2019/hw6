// fms_option.t.cpp - Test general European option pricing
#include <cassert>
#include "fms_option.h"

using namespace fms::option;
using namespace fms::sequence;

int test_moneyness()
{
    double f = 100;
    double s = 0.2*sqrt(0.25);
    double k = 100;
    auto kappa = [](double s) { return s * s / 2; };

    double z = moneyness(f, s, k, kappa);
    double z_ = (kappa(s)) / s;
    assert(z == z_);

    return 0;
}

int test_moneyness_ = test_moneyness();

int test_option_cdf()
{
    //auto kappa = [](double s) { return s * s / 2; };
    auto kappas = constant(0.);

    double x = 0;
    auto P = cdf(x, kappas);
    assert(P == 0.5);

    return 0;
}

int test_option_cdf_ = test_option_cdf();