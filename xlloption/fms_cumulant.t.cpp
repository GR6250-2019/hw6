// fms_cumulant.t.cpp - Test cumulant and cumulants
#include <cassert>
#include "fms_cumulant.h"

using namespace fms::cumulant;


template<class X>
int test_cumulant_scale()
{
    Poisson<>::cumulants kappa(1);
    auto kappa_ = scale(0.5, kappa);
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
    assert(normal<>::cumulant(0.5) == 0.5 * 0.5 / 2);
    normal<>::cumulants kappa;
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
    assert(Poisson<>::cumulant(0.5, 0.25) == 0.25*(exp(0.5) - 1));
    S lambda = 0.5;
    Poisson<>::cumulants kappa(lambda);
    assert(kappa);
    assert(*kappa == lambda);
    assert(*++kappa == lambda);
    assert(*++kappa == lambda);
    assert(*++kappa == lambda);

    return 0;
}

int test_cumulant_Poisson_double = test_cumulant_Poisson<double>();