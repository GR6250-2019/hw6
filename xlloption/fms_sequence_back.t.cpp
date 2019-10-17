// fms_sequence_back.t.cpp - Test the back of a sequence.
#include <cassert>
#include "fms_sequence_back.h"
#include "fms_sequence_iota.h"
#include "fms_sequence_take.h"

using namespace fms::sequence;

template<class X>
int test_sequence_back()
{
    iota<X> i;
    auto i5 = take(5, i);
    auto b = back(i5);
    assert(*b == 4);

    return 0;
}
int test_sequence_back_int = test_sequence_back<int>();