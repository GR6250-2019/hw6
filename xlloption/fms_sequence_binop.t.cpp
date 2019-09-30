// fms_sequence_binop.t.cpp - test binary operations on sequences
#include <cassert>
#include "fms_sequence_binop.h"
#include "fms_sequence_take.h"

int test_binop()
{
    {
        double x[] = { 1, 2, 3 };
        fms::sequence::take s2(2, x), s3(3, x);

        auto add = s2 + s3;
        assert(add);
        assert(*add == 2);
        assert(add);
        ++add;
        assert(*add == 4);
        ++add;
        assert(!add);

        auto mul = s2 * s3;
        assert(mul);
        assert(*mul == 1);
        assert(mul);
        ++mul;
        assert(*mul == 4);
        ++mul;
        assert(!mul);

        auto sub = s2 - s3;
        assert(sub);
        assert(*sub == 0);
        assert(sub);
        ++sub;
        assert(*sub == 0);
        ++sub;
        assert(!sub);

        auto div = s2 / s3;
        assert(div);
        assert(*div == 1);
        assert(div);
        ++div;
        assert(*div == 1);
        ++div;
        assert(!div);

    }

    return 0;
}

int test_binop_ = test_binop();