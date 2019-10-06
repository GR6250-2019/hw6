// xll_sequence.h - Sequences for Excel
#pragma once
#include <set>
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
        // Return a pointer to a copy of the base class.
        virtual sequence* clone() = 0;
        // Delete the copy returned by clone.
        virtual void destroy(sequence*) = 0;
       
    private:
        virtual bool op_bool() const = 0;
        virtual X op_star() const = 0;
        virtual sequence<X>& op_incr() = 0;
    };

    template<class S, class X = double>
    class sequence_impl : public sequence<X> {
        S s;
        using SI = sequence_impl<S, X>;
        static inline std::set<SI*> pool; // keep track of clones
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
        sequence_impl* clone() override
        {
            SI* pi = new SI(*this);
            if (pool.insert(pi).second == false) {
                throw std::runtime_error("squence_impl::clone: duplicate pointer");
            }

            return pi;
        }
        void destroy(sequence<X>* ps) override
        {
            SI* pi = reinterpret_cast<SI*>(ps);
            if (auto i = pool.find(pi); i != pool.end()) {
                delete *i;
                pool.erase(i);
            }
        }
    };

    // Make a copy of sequence.
    template<class X = double>
    class sequence_proxy {
        sequence<X>* pr;
    public:
        sequence_proxy(sequence<X> & r)
            : pr(r.clone())
        {  }
        sequence_proxy(const sequence_proxy& p)
        {
            pr = p.pr->clone();
        }
        sequence_proxy& operator=(const sequence_proxy& p)
        {
            if (this != &pr) {
                pr->destroy(pr);
                pr = p.pr->clone();
            }

            return *this;
        }
        ~sequence_proxy()
        {
            if (pr) {
                pr->destroy(pr);
            }
        }
        operator bool() const
        {
            return *pr;
        }
        X operator*() const
        {
            return *(*pr);
        }
        sequence_proxy& operator++() 
        {
            ++(*pr);

            return *this;
        }
    };
}
