// fms_sequence_sum.t.cpp - test sum
#include <cassert>
#include "fms_sequence_sum.h"
#include "fms_sequence_take.h"

using namespace fms::sequence;

template<class X>
int test_sum()
{
    X x[] = { 1, 2, 3 };
    X s = sum(take(3, x));
    assert(s == 6);
    assert(sum(take(2, x)) == 3);

    return 0;
}

int test_sum_int = test_sum<int>();
int test_sum_float = test_sum<float>();
int test_sum_double = test_sum<double>();
