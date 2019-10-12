// fms_sequence_concatenate.h - Concatenate two sequences.
#pragma once
#include "fms_sequence_item.h"
#include "fms_sequence_traits.h"

namespace fms::sequence {

    template<class S, class T>
    class concatenate {
        S s;
        T t;
    public:
        concatenate(S s, T t)
            : s(s), t(t)
        { }
        operator bool() const
        {
            return s ? s : t;
        }
        auto operator*() const
        {
            return s ? *s : *t;
        }
        concatenate& operator++()
        {
            s ? ++s : ++t;

            return *this;
        }
    };
    template<class S, class X = value_type<S>>
    inline auto cons(X x, S s)
    {
        return concatenate(item(x), s);
    }
}
