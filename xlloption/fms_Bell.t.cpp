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
    double b_ = *b;
    b_ = *++b;
    b_ = *++b;
    b_ = *++b;
    b_ = *++b;

    return 0;
}

int test_bell_ = test_bell();