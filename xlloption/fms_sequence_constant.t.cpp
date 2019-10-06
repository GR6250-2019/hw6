// fms_sequence_constant.t.cpp - Test constant sequences.
#include <cassert>
#include "fms_sequence_constant.h"

using namespace fms::sequence;

int test_sequence_constant()
{
    constant c(42);
    assert(c);
    assert(*c == 42);
    assert(++c && *c == 42);
    assert(++c && *c == 42);

    return 0;
}

int test_sequence_constant_ = test_sequence_constant();