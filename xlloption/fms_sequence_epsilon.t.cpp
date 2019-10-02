// fms_sequence_epsilon.t.cpp -  Test sequences tending to epsilon
#include <cassert>
#include <cmath>
#include "fms_sequence_epsilon.h"
#include "fms_sequence_binop.h"
#include "fms_sequence_power.h"
#include "fms_sequence_epsilon.h"
#include "fms_sequence_factorial.h"
#include "fms_sequence_length.h"
#include "fms_sequence_sum.h"

using namespace fms::sequence;

int test_epsilon()
{
    double x = 1;
    auto s = power(x) / factorial(0.);
    size_t len = length(epsilon(s));
    assert(len == 19);
    double ex = sum(epsilon(s));
    double ex_ = exp(x);
    assert (ex - ex_ == 2*std::numeric_limits<double>::epsilon());

    return 0;
}

int test_epsilon_ = test_epsilon();