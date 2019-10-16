// fms_Bell.t.cpp - Test Bell polynomials.
#include <cassert>
#include "fms_Bell.h"
#include "fms_sequence_constant.h"

using namespace fms;

int test_Bell()
{
    sequence::constant one(1.);
    Bell B(one);
    bell b(one);

    assert(*B == 1);
    assert(*++B == 1);
    assert(*++B == 2);
    assert(*++B == 5);
    assert(*++B == 15);
    
    assert(*b == 1. / 1);
    assert(*++b == 1. / 1);
    assert(*++b == 2. / 2);
    assert(*++b == 5. / (2 * 3));
    assert(*++b == 15. / (2 * 3 * 4));

    return 0;
}

int test_Bell_ = test_Bell();
