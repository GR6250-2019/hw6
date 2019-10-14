// fms_sequence_concatenate.t.cpp - Test concatenating two sequences.
#include <cassert>
#include "fms_sequence_concatenate.h"
#include "fms_sequence_equal.h"
#include "fms_sequence_take.h"
#include "fms_sequence_skip.h"

using namespace fms::sequence;

int test_concatenate()
{
    {
        int i[] = { 1, 2, 3, 4 };
        auto i1 = take(2, i);
        auto i2 = skip(2, take(4, i));
        auto ii = concatenate(i1, i2);
        assert(ii);
        assert(*ii == 1);
        ++ii;
        assert(ii);
        assert(*ii == 2);
        ++ii;
        assert(ii);
        assert(*ii == 3);
        ++ii;
        assert(ii);
        assert(*ii == 4);
        ++ii;
        assert(!ii);
    }
    {
        auto l = list({ 1, 2, 3 });
        auto _l = l; // make a copy to increment
        assert(equal(l, cons(*l, ++_l)));
    }

    return 0;
}

int test_concatenate_ = test_concatenate();