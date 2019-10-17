// fms_sequence_back.h - Return the last element of a sequence.
#pragma once

namespace fms::sequence {

    template<class S>
    inline S back(S s)
    {
        S _s(s);

        while (s) {
            _s = s;
            ++s;
        }

        return _s;
    }
}
