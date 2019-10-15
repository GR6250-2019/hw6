// fms_cumulant_constant.h - Cumulant of a constant random variable.
#pragma once
#include <compare>

namespace fms::cumulant {

    // Cumulants of a constant random variable: c, 0, 0, ...
    template<class S = double>
    class constant {
        S c;
        size_t n = 0;
    public:
        constant(S c = 1)
            : c(c), n(0)
        { }
		const auto operator<=>(const constant&) const = default;
		operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return n == 0 ? c : S(0);
        }
        constant& operator++() 
        {
            ++n;

            return *this;
        }
        S operator()(const S& s) const
        {
            return c * s;
        }
    };
    template<class S = double>
    inline auto shift(constant<S> c, const S&)
    {
        return c;
    }

}