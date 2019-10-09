// fms_sequence_copy.t.cpp - Test copying sequences
#include <cassert>
#include "fms_sequence_copy.h"
#include "fms_sequence_equal.h"
#include "fms_sequence_list.h"
#include "fms_sequence_skip.h"
#include "fms_sequence_take.h"

using namespace fms::sequence;

int test_fms_sequence_copy()
{
    list l({ 1, 2, 3 });
    int i[3];

    assert(3 == copy(l, i));
    assert(equal(l, take(3,i)));

    assert(2 == copy(take(2, skip(1, l)), i));
    assert(i[0] == 2);
    assert(i[1] == 3);

    return 0;
}

int test_fms_sequence_copy_ = test_fms_sequence_copy();

