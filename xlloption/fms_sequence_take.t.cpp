// fms_sequence.t.cpp - test sequences
#include <cassert>
#include "fms_sequence_take.h"

using namespace fms::sequence;

template<class X>
int test_sequence_take()
{
    X x[] = { 1, 2, 3 };
    {
        take s(3, x);
        assert(s);
        assert(*s == 1);
        ++s;
        assert(s);
        assert(*s == 2);
        ++s;
        assert(s);
        assert(*s == 3);
        ++s;
        assert(!s);
    }

    return 0;
}

int test_sequence_take_int = test_sequence_take<int>();
int test_sequence_take_float = test_sequence_take<float>();
int test_sequence_take_double = test_sequence_take<double>();

