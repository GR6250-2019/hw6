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
        // [b, ..., e) -> [--e, ..., b]
        reverse(S b, S e)
            : b(b), e(--e), done(false)
        { }
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
    template<class C>
    inline auto make_reverse(C& c)
    {
        return reverse(c.begin(), c.end());
    }

}
