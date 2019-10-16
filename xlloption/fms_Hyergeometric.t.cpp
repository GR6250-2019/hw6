// fms_Hypergeometric.t.cpp - Test hypergeometric function.
#include <cassert>
#include <limits>
#include "fms_Hypergeometric.h"

using namespace fms;

template<class X = double>
int test_fms_hypergeometric()
{
    constexpr X eps = std::numeric_limits<X>::epsilon();
    {
        // log(1 + x) = x 2_F_1(1,1;2;-x)
        for (X x : {X(-0.5), X(0), X(0.5)}) {
            auto [y, n] = Hypergeometric<X>(1, 1, 2, -x);
            y *= x;
            X y_ = log(1 + x);
            X dy;
            dy = y_ - y;
            assert(fabs(dy) <= eps);
        }
        // (1 - x)^{-a} = 2_F_1(a,1;1;x)
        for (X x : {X(-0.5), X(0), X(0.5)}) {
            for (X a : {X(3), X(2), X(1), X(0.5)}) {
                auto [y, n] = Hypergeometric<X>(a, 1, 1, x);
                X y_ = 1/pow(1 - x, a);
                X dy;
                dy = y_ - y;
                assert(fabs(dy) <= eps);
            }
        }
    }

    return 0;
}
int test_fms_hypergeometric_double = test_fms_hypergeometric<double>();