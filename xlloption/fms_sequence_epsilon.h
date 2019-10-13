// fms_sequence_epsilon.h - terminate at machine epsilon
#pragma once
#include <compare>
#include <limits>
#include "fms_sequence_traits.h"

namespace fms::sequence {

    // machine epsilon terminated sequence
    template<class S, class X = value_type<S>>
    class epsilon {
        S s;
        X scale;
        size_t min;
    public:
        // scale should be the average size of the values
        epsilon(S s, X scale = 1, size_t min = 0)
            : s(s), scale(scale), min(min)
        { }
        const auto operator<=>(const epsilon&) const = default;
        operator bool() const
        {
            if (s) {
                if (min != 0) {
                    return true;
                }

                return *s + scale != scale;
            }

            return false;
        }
        auto operator*() const
        {
            return *s;
        }
        epsilon& operator++()
        {
            if (min != 0) {
                --min;
            }

            ++s;

            return *this;
        }
    };

}