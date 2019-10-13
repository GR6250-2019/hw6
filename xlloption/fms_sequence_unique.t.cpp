// fms_sequence_unique.t.cpp - Test remove duplicates.
#include <cassert>
#include "fms_sequence_unique.h"
#include "fms_sequence_equal.h"
#include "fms_sequence_list.h"

using namespace fms::sequence;

int test_sequence_unique()
{
    {
        auto l = list({ 1, 2, 3 });
        auto u = unique(l);
        assert(u);
        assert(*u == 1);
        ++u;
        assert(u);
        assert(*u == 2);
        ++u;
        assert(u);
        assert(*u == 3);
        ++u;
        assert(!u);
    }
    {
        auto l = list({ 1, 1, 3 });
        auto u = unique(l);
        assert(u);
        assert(*u == 1);
        ++u;
        assert(u);
        assert(*u == 3);
        ++u;
        assert(!u);
    }
    {
        auto l = list({ 1, 1, 1 });
        auto u = unique(l);
        assert(u);
        assert(*u == 1);
        ++u;
        assert(!u);
    }

    return 0;
}
int test_sequence_unique_ = test_sequence_unique();