// fms_sequence.t.cpp - test sequences
#include <cassert>
#include "fms_sequence.h"

using namespace fms;

template<class X>
int test_sequence()
{
    X x[] = { 1, 2, 3 };
    {
        sequence s(3, x);
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

int test_sequence_int = test_sequence<int>();
int test_sequence_float = test_sequence<float>();
int test_sequence_double = test_sequence<double>();

