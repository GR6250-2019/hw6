// fms_sequence_length.h - length of a sequence
#pragma once

namespace fms::sequence {

    template<class S>
    inline size_t length(S s, size_t n = 0)
    {
        while (s) {
            ++n;
            ++s;
        }

        return n;
    }

}
