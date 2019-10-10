// fms_sequence_factorial.h - factorial and Pochhammer symbols
// factorial         : 1, 1, 2       , 2*3            , ...
// raising Pochhammer: 1, x, x(x + 1), x(x + 1)(x + 2), ...
// falling Pochhammer: 1, x, x(x - 1), x(x - 1)(x - 2), ...
#pragma once
#include <compare>

namespace fms::sequence {

    template<class X = double>
    class factorial {
        X x, x_;
        long n;
    public:
        // n = -1 for falling Pochhammer
        factorial(X x = 0, long n = 1)
            : x(x), x_(0), n(n)
        { }
        const auto operator<=>(const factorial&) const = default;
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return x_ == 0 ? 1 : x_;
        }
        factorial& operator++()
        {
            if (x_ == 0) {
                if (x == 0) {
                    x = 1;
                }
                x_ = x;
            }
            else {
                x_ *= (x + n);
                n > 0 ? ++n : --n;
            }

            return *this;
        }

    };

    template<class X = double>
    using Pochhammer = factorial<X>;

}
