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
        // Return a pointer to a copy of the base class.
        virtual sequence* clone() const = 0;
        // Delete the copy returned by clone.
        virtual void destroy(sequence<X>*) const = 0;

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
        sequence_impl(const sequence_impl& rs)
            : s(rs.s)
        {  }
        sequence_impl& operator=(const sequence_impl& rs)
        {
            if (this != &rs) {
                s = rs.s;
            }

            return *this;
        }
        ~sequence_impl()
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
        void destroy(sequence<X>* p) const override
        {
            delete dynamic_cast<sequence_impl<S, X>*>(p);
        }
    };

    // Make a copy of sequence.
    template<class X = double>
    class sequence_proxy : public sequence<X> {
        sequence<X>* ps;
    public:
        sequence_proxy(sequence<X>& s)
            : ps(s.clone())
        {  }
        sequence_proxy(const sequence_proxy& s)
            : ps(s.clone())
        {
        }
        sequence_proxy& operator=(const sequence_proxy& s)
        {
            if (this != &s) {
                ps = s.clone();
            }

            return *this;
        }
        ~sequence_proxy()
        {
            if (ps) {
                ps->destroy(ps);
                ps = nullptr;
            }
        }
        bool op_bool() const
        {
            return *ps;
        }
        X op_star() const
        {
            return  *(*ps);
        }
        sequence_proxy& op_incr() 
        {
            ++(*ps);

            return *this;
        }
        sequence_proxy* clone() const override
        {
            return new sequence_proxy(*ps);
        }
        void destroy(sequence<X>* p) const override
        {
            p->~sequence();
        }
    };
}
