// fms_sequence_iota.t.cpp - Test iota.
#include <cassert>
#include "fms_sequence_iota.h"

using namespace fms::sequence;

template<class X>
int test_iota()
{
    iota<X> i;
    assert(i);
    assert(*i == 0);
	++i;
	assert(i);
	assert(*i == 1);
	++i;
	assert(i);
	assert(*i == 2);

    return 0;
}
int test_iota_double = test_iota<double>();