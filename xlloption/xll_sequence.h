// xll_sequence.h - Sequences for Excel
#pragma once
#include <set>
#include "fms_sequence.h"

namespace xll {
    // NVI type erasure for sequence
    template<class X = double> // a sequence of X
    struct sequence {
        virtual ~sequence()
        { }
        operator bool() const
        {
            return op_bool();
        }
        X operator*() const
        {
            return op_star();
        }
        sequence& operator++()
        {
            return op_incr();
        }
        // Return a pointer to a copy of the derived class.
        virtual sequence* clone() const = 0;
    private:
        virtual bool op_bool() const = 0;
        virtual X op_star() const = 0;
        virtual sequence<X>& op_incr() = 0;
    };

    template<class S, class X = double>
    class sequence_impl : public sequence<X> {
        S s;
    public:
        sequence_impl(S s)
            : s(s)
        { }
        bool op_bool() const override
        {
            return s;
        }
        X op_star() const override
        {
            return *s;
        }
        sequence_impl& op_incr() override
        {
            ++s;

            return *this;
        }
        sequence_impl* clone() const override
        {
            return new sequence_impl(s);
        }
    };

    // Copies of a sequence.
    template<class X = double>
    class sequence_copy {
        std::shared_ptr<sequence<X>> ps;
    public:
        sequence_copy(sequence<X>& s)
            : ps(s.clone())
        { }
        operator bool() const
        {
            return *ps;
        }
        X operator*() const
        {
            return  *(*ps);
        }
        sequence_copy& operator++()
        {
            ++(*ps);

            return *this;
        }
    };
}
