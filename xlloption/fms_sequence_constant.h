// fms_sequence_constant.h - constant sequence
#pragma once
#include <compare>

namespace fms::sequence {

    template<class X = double>
    class constant {
        X x;
     public:
        constant(X x)
            : x(x)
        { }
        const auto operator<=>(const constant&) const = default;
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return x;
        }
        constant& operator++()
        {
            return *this;
        }

    };

}
