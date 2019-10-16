// fms_probability_poisson.t.cpp - Test Poisson distribution
#include <cassert>
#include <initializer_list>
#include "fms_probability_poisson.h"

using namespace fms::probability;

template<class X = double>
int test_fms_probability_poisson()
{
    for (X lambda : {X(0), X(0.1), X(1)}) {
        Poisson<X> p(lambda);

        X x;
        x = X(-1);
        assert(p.pdf(x) == 0);
        assert(p.cdf(x) == 0);
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
		auto kappa = Poisson<X>::cumulants(p);
        assert(*kappa == lambda);
		++kappa;
        assert(*kappa == lambda);

        x = X(0);
        assert(p.pdf(x) == exp(-lambda));
        assert(p.cdf(x) == exp(-lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
 
        x = X(0.5);
        assert(p.pdf(x) == 0);
        assert(p.cdf(x) == exp(-lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));

        x = X(1);
        assert(p.pdf(x) == exp(-lambda)*lambda);
        assert(p.cdf(x) == exp(-lambda)*(1 + lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));

        x = X(1.5);
        assert(p.pdf(x) == 0);
        assert(p.cdf(x) == exp(-lambda) * (1 + lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));

        x = X(2);
        assert(p.pdf(x) == exp(-lambda)*lambda*lambda/2);
        assert(p.cdf(x) == exp(-lambda) * (1 + lambda + lambda*lambda/2));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));

    }

    return 0;
}
int test_fms_probability_poisson_double = test_fms_probability_poisson<double>();
int test_fms_probability_poisson_float = test_fms_probability_poisson<float>();
