// xll_sequence.h - Sequences for Excel
#pragma once
#include "fms_sequence.h"

namespace xll {
    // NVI type erasure for sequence
    template<class X = double> // a sequence of X
    struct sequence {
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
    };
    // Reference to a sequence to use with handles.
    template<class S, class X = double>
    class sequence_ref : public sequence<X> {
        S& s;
    public:
        sequence_ref(S& s)
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
        sequence_ref& op_incr() override
        {
            ++s;

            return *this;
        }
    };
}
