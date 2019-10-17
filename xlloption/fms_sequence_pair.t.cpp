// fms_sequence_pair.t.cpp - Test sequences of pairs.
#include <cassert>
#include "fms_sequence_pair.h"
#include "fms_sequence_iota.h"

using namespace fms::sequence;

template<class X, class Y>
int test_sequence_pair()
{
    iota<X> i0;
    iota<Y> i1;

    auto p = pair(i0, i1);
    assert(p);
    auto p0 = std::pair(X(0), Y(0));
    assert(p0 == *p);

    ++p;
    auto p1 = std::pair(X(1), Y(1));
    assert(p1 == *p);

    return 0;
}
int test_sequence_pair_int = test_sequence_pair<int, int>();
int test_sequence_pair_float_double = test_sequence_pair<float, double>();