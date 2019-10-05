// fms_sequence_concatenate.h - Concatenate two sequences.
#pragma once

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
}
