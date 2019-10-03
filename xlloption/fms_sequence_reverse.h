// fms_sequence_reverse.h - reverse sequence if it has operator--()
#pragma once
#include <compare>

namespace fms::sequence {

    template<class S>
    class reverse {
        const S b; // begin
        S e;       // end
        bool done;
    public:
        // Constructor should be the last element of the sequence, not one past the end.
        // [b, ..., e) -> [--e, ..., b]
        reverse(S b, S e)
            : b(b), e(--e), done(false)
        { }
        /*
        template<class C>
        reverse(C& c)
            : reverse(c.begin(), c.end())
        { }
        */
        const auto operator<=>(const reverse&) const = default;
        operator bool() const
        {
            return !done;
        }
        auto operator*() const
        {
            return *e;
        }
        reverse& operator++()
        {
            if (b == e) {
                done = true;
            }
            else {
                --e;
            }

            return *this;
        }
    };

}
