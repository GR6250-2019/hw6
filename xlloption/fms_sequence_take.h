// fms_sequence_take.h - iterators with operator bool() const
#pragma once

namespace fms::sequence {

    template<class X>
    class take {
        size_t n;
        const X* x;
    public:
        take(size_t n, const X* x)
            : n(n), x(x)
        { }
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
        take& operator++()
        {
            if (n != 0) {
                --n;
                ++x;
            }

            return *this;
        }
    };

}
