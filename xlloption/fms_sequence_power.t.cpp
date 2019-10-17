// fms_sequence_power.t.cpp - Test power sequence.
#include <cassert>
#include "fms_sequence_power.h"

using namespace fms::sequence;

template<class X>
int test_sequence_power()
{
    {
        X c = 2;
        auto p = power(c);
        assert(p);
        assert(1 == *p);
        ++p;
        assert(c == *p);
        ++p;
        assert(c * c == *p);
    }
    {
        X c = 2;
        X cn = 3;
        auto p = power(c, cn);
        assert(p);
        assert(cn == *p);
        ++p;
        assert(cn * c == *p);
        ++p;
        assert(cn * c * c == *p);
    }

    return 0;
}
int test_sequence_power_int = test_sequence_power<int>();