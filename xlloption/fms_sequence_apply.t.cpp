// fms_sequence_apply.t.cpp - Test mapping a function over a sequence.
#include <cassert>
#include "fms_sequence_apply.h"
#include "fms_sequence_iota.h"

using namespace fms::sequence;

#include <type_traits>

struct A {
    int foo(int i)
    {
        return i;
    }
};

int test_A()
{
    using X = std::invoke_result_t<decltype(&A::foo), A, int>;

    return 0;
}

template<class X>
int test_apply()
{
    iota<X> i;
    auto fi = apply([](X j) { return j * j; }, i);
    assert(fi);
    assert(*fi == 0);
    ++fi;
    assert(fi);
    assert(*fi == 1);
    ++fi;
    assert(fi);
    assert(*fi == 4);

    return 0;
}

int test_apply_int = test_apply<int>();