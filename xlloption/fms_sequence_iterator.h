// fms_sequence_iterator - convert container to sequence
#pragma once
#include <compare>
#include <iterator>

namespace fms::sequence {

    template<class I, class J = I>
    class iterator {
        I b;
        J e;
    public:
        iterator(I b, J e)
            : b(b), e(e)
        { }
        const auto operator<=>(const iterator&) const = default;
        operator bool() const
        {
            return b != e;
        }
        auto operator*() const
        {
            return *b;
        }
        iterator& operator++()
        {
            ++b;

            return *this;
        }
    };
    // Assumes c exists over lifetime
    template<class C>
    auto make_iterator(C& c)
    {
        return iterator(c.begin(), c.end());
    }

}
