// fms_sequence_cache.t.cpp - Test sequence caching
#include <cassert>
#include "fms_sequence_cache.h"
#include "fms_sequence_reverse.h"
#include "fms_sequence_take.h"

using namespace fms::sequence;

int test_cache()
{
    double x[] = { 1, 2, 3 };
    auto c = cache(take(3, x));
    assert(c);
    assert(c.size() == 0);
    assert(*c == 1);
    assert(c.size() == 1);
    ++c;
    assert(c.size() == 2);
    assert(c[1] == 2);
    assert(*c == 2);
    ++c;
    assert(c.size() == 3);
    assert(c[2] == 3);
    assert(*c == 3);
    ++c;
    assert(!c);

    const auto& b = c.buffer();
    assert(b.size() == 3);
    assert(b[0] == 1 && b[1] == 2 && b[2] == 3);

    auto rc = reverse(b.begin(), b.end());
    assert(rc);
    assert(*rc == 3);
    assert(++rc);
    assert(*rc == 2);
    ++rc;
    assert(rc);
    assert(*rc == 1);

    return 0;
}

int test_cache_ = test_cache();