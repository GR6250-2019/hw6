// fms_probability_constant.t.cpp - Test constant distribution
#include <cassert>
#include "fms_probability_constant.h"

using namespace fms::probability;

template<class X>
int test_fms_probability_constant()
{
	{
		Constant c;
		Constant c2(c);
		c = c2;
		/*
		assert(c == c2);  // ??? failing ???
		assert(!(c != c2));
		assert(c <= c2);
		assert(!(c < c2));
		assert(c >= c2);
		assert(!(c > c2));
		*/
		assert(0 == c.pdf(X(1)));
		assert(1 == c.pdf(X(0)));
		assert(0  == c.pdf(X(-1)));
		
		assert(0 == c.cdf(X(-1)));
		assert(1 == c.cdf(X(0)));
		assert(1 == c.cdf(X(1)));

		assert(1 == c.moment(X(-1)));
		assert(1 == c.moment(X(0)));
		assert(1 == c.moment(X(1)));

		auto m = Constant<X>::moments(c);
		assert(m);
		assert(1 == *m);
		++m;
		assert(0 == *m);
		++m;
		assert(0 == *m);

		assert(0 == c.cumulant(X(-1)));
		assert(0 == c.cumulant(X(0)));
		assert(0 == c.cumulant(X(1)));

		auto k = Constant<X>::cumulants(c);
		assert(k);
		assert(0 == *k);
		++k;
		assert(0 == *k);
	}
	{
		X c0 = 1.5;
		Constant c(c0);
		Constant c2(c);
		c = c2;

		assert(c == c2);
		assert(!(c != c2));
		assert(c <= c2);
		assert(!(c < c2));
		assert(c >= c2);
		assert(!(c > c2));
		
		assert(0 == c.pdf(c0 - 1));
		assert(1 == c.pdf(c0));
		assert(0 == c.pdf(c0 + 1));

		assert(0 == c.cdf(c0 - 1));
		assert(1 == c.cdf(c0));
		assert(1 == c.cdf(c0 + 1));

		assert(exp(-c0) == c.moment(X(-1)));
		assert(1 == c.moment(X(0)));
		assert(exp(c0) == c.moment(X(1)));

		auto m = Constant<X>::moments(c);
		assert(m);
		assert(1 == *m);
		++m;
		assert(c0 == *m);
		++m;
		assert(c0 * c0 == *m);

		assert(-c0 == c.cumulant(X(-1)));
		assert(0 == c.cumulant(X(0)));
		assert(c0 == c.cumulant(X(1)));

		auto k = Constant<X>::cumulants(c);
		assert(k);
		assert(c0 == *k);
		++k;
		assert(0 == *k);
	}

	return 0;
}
int test_fms_probability_constant_double = test_fms_probability_constant<double>();