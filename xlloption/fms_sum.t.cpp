// fms_sum.t.cpp - test sum
#include <cassert>
#include "fms_sum.h"
#include "fms_sequence.h"

using namespace fms;

template<class X>
int test_sum()
{
    X x[] = { 1, 2, 3 };
    X s = sum(sequence(3, x));
    assert(s == 6);
    assert(sum(sequence(2, x)) == 3);

    return 0;
}

int test_sum_int = test_sum<int>();
int test_sum_float = test_sum<float>();
int test_sum_double = test_sum<double>();
