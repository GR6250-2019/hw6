// fms_sequence_null.cpp - Zero terminated sequence.
#include <cassert>
#include "fms_sequence_null.h"
#include "fms_sequence_length.h"

using namespace fms::sequence;

template<class X>
int test_fms_sequence_null()
{
    X x[] = { 1, 2, 3, 0 };
    auto s = null(x);
    assert(3 == length(s));

    return 0;
}
int test_fms_sequence_char = test_fms_sequence_null<char>();