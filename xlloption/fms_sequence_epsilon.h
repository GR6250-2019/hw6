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
        size_t min, max;
    public:
        // scale should be the average size of the values
        epsilon(S s, X scale = 1, size_t min = 0, size_t max = std::numeric_limits<size_t>::max())
            : s(s), scale(scale), min(min), max(max)
        { }
        const auto operator<=>(const epsilon&) const = default;
        operator bool() const
        {
            if (s) {
                if (min != 0) {
                    return true;
                }
                if (max == 0) {
                    return false;
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
            if (max != 0) {
                --max;
            }

            ++s;

            return *this;
        }
    };

}