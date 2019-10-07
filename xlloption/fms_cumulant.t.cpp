// fms_cumulant.t.cpp - Test cumulant and cumulants
#include <cassert>
#include "fms_sequence.h"
#include "fms_cumulant.h"

using namespace fms::sequence;
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

int test_cumulant_sum()
{
    normal n;
    Poisson P(1.);
    double c[] = { 2, 3 };

    auto sp = sum_product(c, 2, n, P);
    for (double s : {0., 0.1, 1.}) {
        assert(sp(s) == c[0] * n(s) + c[1] * P(s));
    }

    return 0;
}
int test_cumulant_sum_ = test_cumulant_sum();

int test_cumulant_sum_product()
{
    {
        constant<> one(1);
        double c[] = { 1, 2, 3 };
        auto sp = sum_product(&c[0], 3, one, one, one);
        assert(sp);
        assert(*sp == 1 + 2 + 3);
        ++sp;
        assert(sp);
        assert(*sp == 1 + 4 + 9);
        ++sp;
        assert(sp);
        assert(*sp == 1 + 8 + 27);
    }
    {
        constant<> one(1);
        double c[] = { 1, 2, 3 };
        auto t = std::tuple{ one, one, one };
        auto sp = sum_product(&c[0], 3, one, one, iota{});
        assert(sp);
        assert(*sp == 1 + 2 + 3*0);
        ++sp;
        assert(sp);
        assert(*sp == 1 + 4 + 9*1);
        ++sp;
        assert(sp);
        assert(*sp == 1 + 8 + 27*2);
    }

    return 0;
}

int test_cumulant_sum_product_ = test_cumulant_sum_product();

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