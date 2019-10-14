// fms_sequence_iterator.t.cpp - Test sequence iterators
#include <cassert>
#include <vector>
#include "fms_sequence_iterator.h"

using namespace fms::sequence;

int test_sequence_iterator()
{
    std::vector<int> v = { 1, 2, 3 };
    auto i = make_iterator(v);
    assert(i);
    assert(*i == 1);
    ++i;
    assert(i);
    assert(*i == 2);
    ++i;
    assert(i);
    assert(*i == 3);
    ++i;
    assert(!i);
    {
        std::string s("ab");
        auto ss = make_iterator(s);
        assert(ss);
        assert(*ss == 'a');
        ++ss;
        assert(ss);
        assert(*ss == 'b');
        ++ss;
        assert(!ss);
    }

    return 0;
}
int test_sequence_iterator_ = test_sequence_iterator();