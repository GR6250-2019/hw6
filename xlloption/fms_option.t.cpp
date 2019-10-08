// fms_option.t.cpp - Test general European option pricing
#include <cassert>
#include "fms_option.h"
#include "fms_Poisson.h"

using namespace fms::option;
using namespace fms::sequence;
using namespace fms::cumulant;

int test_moneyness()
{
    double f = 100;
    double s = 0.2*sqrt(0.25);
    double k = 90;
    auto kappa = [](double s) { return s * s / 2; };

    double z = moneyness(f, s, k, kappa);
    double z_ = (kappa(s) + log(k/f)) / s;
    assert(z == z_);

    return 0;
}

int test_moneyness_ = test_moneyness();

int test_option_cdf()
{
    {
        auto kappas = normal<>();

        for (double x : {-1., 0., 1., 1.1}) {
            auto P = cdf(x, kappas);
            assert(P == fms::normal::cdf(x));
        }
    }
    {
        double mu = 0.5;
        auto kappas = normal( mu, 1. );

        for (double x : {-1., 0., 1., 1.1}) {
            auto P = cdf(x, kappas);
            assert(P == fms::normal::cdf(x - mu));
        }
    }
    {
        double mu = 0.5;
        double sigma = 2;
        auto kappas = normal(mu, sigma);

        for (double x : {-1., 0., 1., 1.1}) {
            auto P = cdf(x, kappas);
            assert(P == fms::normal::cdf((x - mu)/sigma));
        }
    }
    /*
    {
        double lambda = 0.5;
        auto kappas = Poisson(lambda);

        for (double x : {-1., 0., 1., 1.1}) {
            auto P = cdf(x, kappas);
            assert(P == fms::Poisson::cdf((x - lambda) / lambda, lambda));
        }
    }
    */

    return 0;
}

int test_option_cdf_ = test_option_cdf();