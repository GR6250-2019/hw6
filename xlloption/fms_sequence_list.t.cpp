// fms_sequence_list.t.cpp - Test list sequence
#include <cassert>
#include "fms_sequence_list.h"

using namespace fms::sequence;

template<class X>
int test_sequence_list()
{
    list s({ X(1), X(2), X(3) });
    
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

    return 0;
}

int test_sequence_list_double = test_sequence_list<double>();
