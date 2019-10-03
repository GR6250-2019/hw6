// fms_sequence_reverse.t.cpp Test reverse sequence
#include <cassert>
#include <vector>
#include "fms_sequence_reverse.h"
#include "fms_sequence_take.h"

using namespace fms::sequence;

template<class X>
int test_reverse()
{
    std::vector<X> s = { 1, 2, 3 };
    {
        auto r = reverse(s.begin(), s.end());
        assert(r);
        assert(*r == 3);
        ++r;
        assert(r);
        assert(*r == 2);
        ++r;
        assert(r);
        assert(*r == 1);
        ++r;
        assert(!r);
    }
    {
        auto r = make_reverse(s);
        assert(r);
        assert(*r == 3);
        ++r;
        assert(r);
        assert(*r == 2);
        ++r;
        assert(r);
        assert(*r == 1);
        ++r;
        assert(!r);
    }

    return 0;
}

int test_reverse_double = test_reverse<double>();