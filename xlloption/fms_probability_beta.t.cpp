// fms_probability_beta.t.cpp - Test the Beta distribution.
#include <cassert>
#include "fms_probability_beta.h"

using namespace fms::probability;

template<class X>
int test_probability_beta()
{
	{
		X alpha = X(0.5);
		X beta = X(2.);
		Beta B(alpha, beta);
		auto m = Beta<X>::moments(B);
		assert(m);
		assert(*m == 1);
		++m;
		assert(*m == alpha / (alpha + beta));
		++m;
		assert(*m == (alpha * (alpha + 1) / ((beta + alpha) * (beta + alpha + 1))));
	}

	return 0;
}
int test_probability_beta_double = test_probability_beta<double>();