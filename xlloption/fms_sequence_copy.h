// fms_sequence_copy.h - Copy one sequence to another
#pragma once

namespace fms::sequence {

    template<class S, class T>
    inline void copy(S s, T t)
    {
        while (s) {
            *t = *s;
            ++s;
            ++t;
        }
    }

}
