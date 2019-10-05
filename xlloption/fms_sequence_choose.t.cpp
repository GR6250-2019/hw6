// fms_sequence_choose.t.cpp - Test n choose k sequence
#include <cassert>
#include "fms_sequence_choose.h"

using namespace fms::sequence;

template<class X>
int test_choose()
{
    {
        choose C(X(0));
        assert(C && *C == 1);
        assert(!++C);
    }
    {
        choose C(X(1));
        assert(C && *C == 1);
        assert(++C && *C == 1);
        assert(!++C);
    }
    {
        choose C(X(4));
        assert(C);
        assert(*C == 1);
        ++C;
        assert(C);
        assert(*C == 4);
        ++C;
        assert(C);
        assert(*C == 6);
        ++C;
        assert(C);
        assert(*C == 4);
        ++C;
        assert(C);
        assert(*C == 1);
        ++C;
        assert(!C);
        }

    return 0;
}

int test_choose_double = test_choose<double>();