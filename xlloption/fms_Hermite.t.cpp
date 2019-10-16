// fms_Hermite.t.cpp - Hermite polynomial test
#include <cassert>
#include "fms_Hermite.h"

using namespace fms;

template<class X>
int test_Hermite(X x)
{
    Hermite H(x);
    assert(H);
    assert(*H == X(1)); // H0
    ++H;
    assert(H);
    assert(*H == x); // H1
    ++H;
    assert(H);
    assert(*H == x * x - 1); // H2
    ++H;
    assert(H);
    assert(*H == x * (x * x - 1) - 2 * x); // H3

    return 0;
}

int test_Hermite0_ = test_Hermite(0);
int test_Hermite1_ = test_Hermite(1);
int test_Hermite2_ = test_Hermite(2);
