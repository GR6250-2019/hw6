// fms_sequence_flatten.t.cpp - Test flattening sequences.
#include <cassert>
#include "fms_sequence_flatten.h"
#include "fms_sequence_list.h"

using namespace fms::sequence;

template<class X>
int test_fms_sequence_flatten()
{
    auto l0 = list({ 0, 1 });
    auto l1 = list({ 2, 3 });
    auto l01 = list({ l0, l1 });
    auto f = flatten(l01);
    assert(f);
    assert(*f == 0);
    ++f;
    assert(*f == 1);
    ++f;
    assert(*f == 2);
    ++f;
    assert(*f == 3);
    ++f;
    assert(!f);

    return 0;
}
int test_fms_sequence_flatten_int = test_fms_sequence_flatten<int>();