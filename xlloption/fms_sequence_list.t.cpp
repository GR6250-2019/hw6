// fms_sequence_list.t.cpp - Test list sequence
#include <cassert>
#include "fms_sequence_list.h"
#include "fms_sequence_cache.h"
#include "fms_sequence_concatenate.h"
#include "fms_sequence_length.h"
using namespace fms::sequence;

template<class S>
void test_list(S s)
{
    assert(length(s) == 3);
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
    --s;
    assert(s);
    assert(*s == 3);

    s.reset();
    assert(s.size() == 3);
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

template<class X>
int test_sequence_list()
{
    test_list(list({ X(1), X(2), X(3) }));
    std::vector<X> s{ 1, 2, 3 };
    test_list(list(s));
    test_list(list(3, &s[0]));
    X one = 1, two = 2, three = 3;
    auto l = cache(concatenate(list(1, &one), concatenate(list(1, &two), list(1, &three))));
    assert(length(l) == 3);
    test_list(l);

    return 0;
}

int test_sequence_list_double = test_sequence_list<double>();
