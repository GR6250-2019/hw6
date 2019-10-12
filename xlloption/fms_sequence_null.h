// fms_sequence_null.h - terminate at 0
#pragma once
#include <compare>
#include "fms_sequence_traits.h"

namespace fms::sequence {

    template<class S>
    class null {
        S s;
    public:
        null(S s)
            : s(s)
        { }
        const auto operator<=>(const null&) const = default;
        operator bool() const
        {
            return *s != 0;
        }
        auto operator*() const
        {
            return *s;
        }
        null& operator++()
        {
            ++s;

            return *this;
        }
    };

}