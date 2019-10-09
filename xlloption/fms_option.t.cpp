// fms_option.t.cpp - Test general European option pricing
#include <cassert>
#include "fms_option.h"
#include "fms_cumulant_normal.h"
#include "fms_probability_poisson.h"
#include "fms_probability_normal.h"

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
        auto kappas = Normal<>();

        for (double x : {-1., 0., 1., 1.1}) {
            double p;
            p = cdf(x, kappas);
            assert(p == fms::normal::cdf(x));
            p = pdf(x, kappas);
            assert(p == fms::normal::pdf(x));
        }
    }
    {
        double mu = 0.5;
        auto kappas = Normal( mu, 1. );

        for (double x : {-1., 0., 1., 1.1}) {
            double p, p_;
            p = cdf(x, kappas);
            p_ = fms::normal::cdf(x - mu);
            assert(p - p_ == 0);
            p = pdf(x, kappas);
            p_ = fms::normal::pdf(x - mu);
            assert(p - p_ == 0);
        }
    }
    {
        double mu = 0.5;
        double sigma = 2;
        auto kappas = Normal(mu, sigma);

        for (double x : {-1., 0., 1., 1.1}) {
            double p;
            p = cdf(x, kappas);
            assert(p == fms::normal::cdf((x - mu)/sigma));
            p = pdf(x, kappas);
            assert(p == fms::normal::pdf((x - mu)/sigma)/sigma);
        }
    }
    {
        double lambda = 0.1;
        fms::probability::Poisson poisson(lambda);
        auto kappas = Poisson(lambda);

        for (double x : {-1., 0., 1., 1.1}) {
            double P = pdf(x, kappas);
            double P_ = poisson.pdf(x);
            double dP;
            dP = P - P_;
        }
    }

    return 0;
}

int test_option_cdf_ = test_option_cdf();