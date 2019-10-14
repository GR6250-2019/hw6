// fms_sequence_null.cpp - Zero terminated sequence.
#include <cassert>
#include "fms_sequence_null.h"
#include "fms_sequence_length.h"
#include "fms_sequence_list.h"

using namespace fms::sequence;

template<class X>
int test_fms_sequence_null()
{
    {
        X x[] = { 1, 2, 0 };
        auto s = null(x);
        assert(2 == length(s));
        assert(s);
        assert(*s == 1);
        ++s;
        assert(s);
        assert(*s == 2);
        ++s;
        assert(!s);
    }
    {
        auto ab = null("ab");
        auto ab2(ab);
        ab = ab2;
        assert(ab);
        assert('a' == *ab);
        ++ab;
        assert(ab);
        assert('b' == *ab);
        ++ab;
        assert(!ab);
    }

    return 0;
}
int test_fms_sequence_char = test_fms_sequence_null<char>();