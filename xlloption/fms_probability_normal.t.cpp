// fms_probability_normal.t.cpp - Test Normal probability distribution.
#include <cassert>
#include "fms_probability_normal.h"

using namespace fms::probability;

template<class X>
int test_fms_probability_normal()
{
	{
		Normal<X> N;
		Normal<X> N2(N);
		N = N2;
		assert(N == N2);
		assert(N.cumulant(0.5) == 0.5 * 0.5 / 2);
		auto kappa = Normal<X>::cumulants(N);
		assert(kappa);
		assert(*kappa == 0);
		assert(*++kappa == 1);
		assert(*++kappa == 0);
		assert(*++kappa == 0);
	}

	{
		X mu = 0.5;
		X sigma = 2;
		Normal<X> N(mu, sigma);
		auto kappa = Normal<X>::cumulants(N);
		//auto kappa_ = shift(kappa, s);
		/*
		for (double u : {-1., 0., 1.}) {
			double ku_ = kappa_(u);
			double ku = kappa(u + s) - kappa(s);
			double dku = ku_ - ku;
			assert(fabs(dku) <= std::numeric_limits<double>::epsilon());
		}
		*/
	}

    return 0;
}

int test_fms_probability_normal_double = test_fms_probability_normal<double>();