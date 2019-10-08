// fms_probability_Poisson.t.cpp - Test Poisson distribution
#include <cassert>
#include <initializer_list>
#include "fms_probability_Poisson.h"

using namespace fms::probability;

template<class X = double>
int test_fms_probability_Poisson()
{
    for (X lambda : {X(0), X(0.1), X(1)}) {
        Poisson<X> p(lambda);

        X x;
        x = X(-1);
        assert(p.pdf(x) == 0);
        assert(p.cdf(x) == 0);
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
        assert(p.cumulants(0) == 0);
        assert(p.cumulants(1) == lambda);
        assert(p.cumulants(2) == lambda);

        x = X(0);
        assert(p.pdf(x) == exp(-lambda));
        assert(p.cdf(x) == exp(-lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
        assert(p.cumulants(0) == 0);
        assert(p.cumulants(1) == lambda);
        assert(p.cumulants(2) == lambda);

        x = X(0.5);
        assert(p.pdf(x) == 0);
        assert(p.cdf(x) == exp(-lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
        assert(p.cumulants(0) == 0);
        assert(p.cumulants(1) == lambda);
        assert(p.cumulants(2) == lambda);

        x = X(1);
        assert(p.pdf(x) == exp(-lambda)*lambda);
        assert(p.cdf(x) == exp(-lambda)*(1 + lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
        assert(p.cumulants(0) == 0);
        assert(p.cumulants(1) == lambda);
        assert(p.cumulants(2) == lambda);

        x = X(1.5);
        assert(p.pdf(x) == 0);
        assert(p.cdf(x) == exp(-lambda) * (1 + lambda));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
        assert(p.cumulants(0) == 0);
        assert(p.cumulants(1) == lambda);
        assert(p.cumulants(2) == lambda);

        x = X(2);
        assert(p.pdf(x) == exp(-lambda)*lambda*lambda/2);
        assert(p.cdf(x) == exp(-lambda) * (1 + lambda + lambda*lambda/2));
        assert(p.cumulant(x) == lambda * (exp(x) - 1));
        assert(p.cumulants(0) == 0);
        assert(p.cumulants(1) == lambda);
        assert(p.cumulants(2) == lambda);

    }

    return 0;
}
int test_fms_probability_Poisson_double = test_fms_probability_Poisson<double>();
int test_fms_probability_Poisson_float = test_fms_probability_Poisson<float>();
