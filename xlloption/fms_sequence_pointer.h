// fms_sequence_pointer.h - counted array
#pragma once
#include <compare>

namespace fms::sequence {

    template<class X>
    class pointer {
        size_t n;
        const X* x;
    public:
        pointer(size_t n, const X* x)
            : n(n), x(x)
        { }
        const auto operator<=>(const pointer&) const = default;
        size_t size() const
        {
            return n;
        }
        const X* begin() const
        {
            return x;
        }
        const X* end() const
        {
            return x + n;
        }
        operator bool() const
        {
            return n != 0;
        }
        X operator*() const
        {
            return *x;
        }
        pointer& operator++()
        {
            if (n != 0) {
                --n;
                ++x;
            }

            return *this;
        }
    };
}
