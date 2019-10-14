// fms_sequence_flatten.t.cpp - Test flattening sequences.
#include <cassert>
#include "fms_sequence_flatten.h"
#include "fms_sequence_apply.h"
#include "fms_sequence_cache.h"
#include "fms_sequence_concatenate.h"
#include "fms_sequence_copy.h"
#include "fms_sequence_equal.h"
#include "fms_sequence_item.h"
#include "fms_sequence_iterator.h"
#include "fms_sequence_list.h"
#include "fms_sequence_constant.h"
#include "fms_sequence_null.h"
#include "fms_sequence_skip.h"

using namespace fms::sequence;

template<class X>
int test_fms_sequence_flatten()
{
    {
        auto l0 = list({ 0, 1 });
        auto l1 = list({ 2, 3 });
        auto l01 = list({ l0, l1 });
        auto f = flatten(l01);
        assert(f);
        assert(*f == 0);
        ++f;
        assert(*f == 1);
        ++f;
        assert(*f == 2);
        ++f;
        assert(*f == 3);
        ++f;
        assert(!f);
    }
    {
        null ab("ab");
        //auto _ = item("_");
        auto prepend = [](char c) { return list({ '_', c }); };
        auto comma = cache(apply(prepend, ab));
        assert(equal(*comma, list({ '_', 'a' })));        
        ++comma;
        assert(equal(*comma, list({ '_', 'b' })));
        ++comma;
        assert(!comma);
        
        // {{'_', 'a'}, {'_', 'b'}}
        comma = cache(apply(prepend, ab));
        auto _ab = flatten(comma);
        assert(_ab);
        assert(*_ab == '_');
        ++_ab;
        assert(_ab);
        assert(*_ab == 'a');
        ++_ab;
        assert(_ab);
        assert(*_ab == '_');
        ++_ab;
        assert(_ab);
        assert(*_ab == 'b');
        ++_ab;
        assert(!_ab);
    }
    {
        auto prepend = [](char c) { return list({ '_', c }); };
        auto f = cache(apply(prepend, null("ab")));
        assert(equal(flatten(f), null("_a_b")));

    }
    {
        auto l = list({ "a", "bc", "def" });
        auto prepend = [](auto x) { return std::string(", ") + x; };
        std::vector<std::string> s({ ", a", ", bc", ", def" });
        auto F = [](std::string s) { return make_iterator(s); };
        auto f = apply(F, make_iterator(s));
        auto _f = *f;
        _f = *++f;
        _f = *++f;
        //assert(equal(f, make_iterator(s)));
        //to g = cache(apply(make_iterator<std::string>, f));
        /*
        auto h = flatten(g);
        auto i = *h;
        i = *++h;
        i = *++h;
        i = *++h;
        i = *++h;
        */
        //assert(equal(f, null(", a, bc, def")));
    }
    {
        auto l = list({ 1, 2, 3 });
        auto f = [](auto i) { return list({ 0, i }); };
        auto afl = apply(f, l);
        auto fc = flatten(cache(afl));
        assert(equal(fc, list({ 0, 1, 0, 2, 0, 3 })));
    }
    {
        auto l = list({ 1, 2, 3 });
        auto f = [](auto i) { return list({ 0, i }); };
        auto afl = apply(f, l);
        auto fc = flatten(cache(afl));
        assert(equal(skip(1,fc), list({1, 0, 2, 0, 3 })));
    }
    {
        auto l = list({ 1, 2, 3 });
        auto l_ = list({ 1, 0, 2, 0, 3 });
        auto f = [](auto i) { return list({ 0, i }); };
        assert(equal(l_, skip(1, flatten(cache(apply(f,l))))));
    }
    {
        auto l = null("ab");
        auto f = [](auto c) { return list({ ',', c }); };
        auto fl = skip(1, flatten(cache(apply(f, l))));
        std::string s;
        copy(fl, std::back_inserter(s));
        assert(s == "a,b");
    }


    return 0;
}
int test_fms_sequence_flatten_int = test_fms_sequence_flatten<int>();