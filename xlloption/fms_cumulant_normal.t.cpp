// fms_cumulant_normal.t.cpp - Test Normal cumulant.
#include <cassert>
#include <limits>
#include "fms_cumulant.h"
#include "fms_cumulant_normal.h"

using namespace fms::cumulant;

template<class S>
int test_cumulant_normal()
{
    {
        Normal<> kappa;
        assert(kappa(0.5) == 0.5 * 0.5 / 2);
        assert(kappa);
        assert(*kappa == 0);
        assert(*++kappa == 1);
        assert(*++kappa == 0);
        assert(*++kappa == 0);
        }

    {
        double s = 0.1;
        Normal<> kappa;
        auto kappa_ = shift(kappa, s);
        for (double u : {-1., 0., 1.}) {
            double ku_ = kappa_(u);
            double ku = kappa(u + s) - kappa(s);
            double dku = ku_ - ku;
            assert(fabs(dku) <= std::numeric_limits<double>::epsilon());
        }
    }

    return 0;
}

int test_cumulant_normal_double = test_cumulant_normal<double>();

