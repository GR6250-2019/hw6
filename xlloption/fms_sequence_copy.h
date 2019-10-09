// fms_sequence_copy.h - Copy one sequence to another and return number copied.
#pragma once

namespace fms::sequence {

    template<class S, class T>
    inline size_t copy(S s, T t)
    {
        size_t n = 0;
        while (s) {
            *t = *s;
            ++s;
            ++t;
            ++n;
        }

        return n;
    }

}
