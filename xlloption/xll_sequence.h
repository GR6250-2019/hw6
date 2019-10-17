// xll_sequence.h - Sequences for Excel
#pragma once

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

    // Manage the lifetime of a sequence.
    template<class X = double>
    class sequence_copy {
        sequence<X>* ps;
    public:        
        sequence_copy(const sequence<X>& s)
            : ps(s.clone())
        { }    
        sequence_copy(const sequence_copy& s)
            : ps(s.ps->clone())
        { }
        sequence_copy& operator=(const sequence_copy& s)
        {
            if (this != &s) {
                delete ps;
                ps = s.ps->clone();
            }

            return *this;
        }
        ~sequence_copy()
        {
            delete ps;
        }
        
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
