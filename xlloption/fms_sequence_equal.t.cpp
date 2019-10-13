// fms_sequence_equal.t.cpp - Test equality of sequences
#include <cassert>
#include "fms_sequence_equal.h"
#include "fms_sequence_iota.h"
#include "fms_sequence_pointer.h"
#include "fms_sequence_take.h"

using namespace fms::sequence;

int test_sequence_equal()
{
    {
        int s[] = { 1, 2, 3 };
        pointer sp(3, s);
        assert(equal(sp, take(3, iota(1))));
        assert(equal(take(0, sp), take(0, sp)));
    }

    return 0;
}

int test_sequence_equal_ = test_sequence_equal();