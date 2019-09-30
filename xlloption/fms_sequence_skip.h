// fms_sequence_skip.h - skip elements of a sequence
#pragma once

namespace fms::sequence {

    template<class S>
    inline S skip(size_t n, S s)
    {
        while (s && n > 0) {
            --n;
            ++s;
        }

        return s
    }

}
