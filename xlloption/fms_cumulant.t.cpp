// fms_cumulant.t.cpp - Test cumulant and cumulants
#include <cassert>
#include "fms_cumulant.h"

using namespace fms::cumulant;


template<class X>
int test_cumulant_scale()
{
    Poisson kappa(X(1));
    auto kappa_ = scale(X(0.5), kappa);
    assert(*kappa == 1);
    assert(kappa_);
    assert(*kappa_ == 0.5);
    ++kappa;
    ++kappa_;
    assert(*kappa == 1);
    assert(*kappa_ == 0.25);
    ++kappa;
    ++kappa_;
    assert(*kappa == 1);
    assert(*kappa_ == 0.125);

    return 0;
}

int test_cumulant_scale_double = test_cumulant_scale<double>();

template<class S>
int test_cumulant_normal()
{
    normal<> kappa;
    assert(kappa(0.5) == 0.5 * 0.5 / 2);
    assert(kappa);
    assert(*kappa == 0);
    assert(*++kappa == 1);
    assert(*++kappa == 0);
    assert(*++kappa == 0);

    return 0;
}

int test_cumulant_normal_double = test_cumulant_normal<double>();

template<class S>
int test_cumulant_Poisson()
{
    S lambda = 0.5;
    Poisson<> kappa(lambda);
    assert(kappa(0.25) == lambda * (exp(0.25) - 1));
    assert(kappa);
    assert(*kappa == lambda);
    assert(*++kappa == lambda);
    assert(*++kappa == lambda);
    assert(*++kappa == lambda);

    return 0;
}

int test_cumulant_Poisson_double = test_cumulant_Poisson<double>();