// fms_sequence_apply.h - map a function over a sequence
#pragma once
#include <compare>

namespace fms::sequence {

    template<class F, class S>
    class apply {
        F f;
        S s;
    public:
        apply(const F& f, const S& s)
            : f(f), s(s)
        { }
        const auto operator<=>(const apply&) const = default;
        operator bool() const
        {
            return s;
        }
        auto operator*() const
        {
            return f(*s);
        }
        apply& operator++()
        {
            ++s;

            return *this;
        }

    };

}
