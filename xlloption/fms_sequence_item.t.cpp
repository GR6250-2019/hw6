// fms_sequence_item.t.cpp - Test a one item list.
#include <cassert>
#include "fms_sequence_item.h"

using namespace fms::sequence;

template<class X>
int test_fms_sequence_item()
{
    X x = 1;
    auto ix = item(x);
    assert(ix);
    assert(*ix == x);
    ++ix;
    assert(!ix);

    return 0;
}
int test_fms_sequence_item_double = test_fms_sequence_item<double>();