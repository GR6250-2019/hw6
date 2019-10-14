// fms_cumulant_constant.t.cpp - Test cumulant of constant random variable.
#include <cassert>
#include <limits>
#include "fms_cumulant_constant.h"

using namespace fms::cumulant;

template<class S>
int test_cumulant_constant()
{
    {
        auto c = constant(1.);
    
        assert(*c == 1.);
        ++c;
        assert(*c == 0);
        ++c;
        assert(*c == 0);
    }

    {
        auto c = constant(1.);

        auto c_ = shift(c, 100.);
        assert(*c_ == 1.);
        ++c_;
        assert(*c_ == 0.);
    }
    
    return 0;
}

int test_cumulant_constant_double = test_cumulant_constant<double>();

