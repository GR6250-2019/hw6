// fms_sequence_sum.h - sum a sequence
#pragma once
#include <stdexcept>
#include <type_traits>

namespace fms::sequence {

    template<class S>
    inline auto sum(S s, decltype(*s) x = 0)
    {
        while (s) {
            x += *s;
            ++s;
        }

        return x;
    }

}
