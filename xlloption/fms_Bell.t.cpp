// fms_Bell.t.cpp - Test Bell polynomials.
#include <cassert>
#include "fms_Bell.h"
#include "fms_sequence_constant.h"

using namespace fms;

int test_Bell()
{
    return 0;
}

int test_Bell_ = test_Bell();

int test_bell()
{
    sequence::constant one(1.);
    bell b(one);
    assert(*b == 1./1);
    assert(*++b == 1./1);
    assert(*++b == 2. / 2);
    assert(*++b == 5./(2*3));
    assert(*++b == 15./(2*3*4));

    return 0;
}

int test_bell_ = test_bell();