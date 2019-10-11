// fms_sequence_epsilon.t.cpp -  Test sequences tending to epsilon
#include <cassert>
#include <cmath>
#include "fms_sequence_epsilon.h"
#include "fms_sequence_binop.h"
#include "fms_sequence_constant.h"
#include "fms_sequence_power.h"
#include "fms_sequence_epsilon.h"
#include "fms_sequence_factorial.h"
#include "fms_sequence_length.h"
#include "fms_sequence_sum.h"
#include "fms_sequence_take.h"

using namespace fms::sequence;

int test_epsilon()
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    double x = 1;
    auto s = power(x) / factorial(0.);
    size_t len = length(epsilon(s));
    assert(len == 19);
    double ex = sum(epsilon(s));
    double ex_ = exp(x);
    assert (ex - ex_ == 2*eps);

    {
        auto p = power(0.5);
        auto e = epsilon(p);
        auto n = length(e);
        assert(n == 53);
    }
    {
        auto p = power(0.5);
        auto e = epsilon(p, 1., 60);
        auto n = length(e);
        assert(n == 60);
    }
    {
        auto c = constant(eps / 2);
        assert(0 == length(epsilon(c)));
        assert(0 == sum(epsilon(c)));
        assert(2 * eps == sum(take(4, c)));
    }

    return 0;
}

int test_epsilon_ = test_epsilon();