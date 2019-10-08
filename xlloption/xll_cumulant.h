// xll_cumlant.h - Cumulants for Excel
#pragma once
#include "fms_cumulant.h"
#include "xll_sequence.h"

namespace xll {

    template<class S = double>
    struct cumulant : public sequence<S> {
        virtual ~cumulant()
        { }
        S operator()(const S& s) const
        {
            return op_value(s);
        }
    private:
        virtual S op_value(const S&) const = 0;
    };
    template<class K, class S = fms::cumulant::value_type<K>>
    class cumulant_impl : public cumulant<S> {
        K k;
    public:
        cumulant_impl(K k)
            : k(k)
        { }
        ~cumulant_impl()
        { }
        S op_value(const S& s) const override
        {
            return k(s);
        }
        bool op_bool() const override
        {
            return k;
        }
        S op_star() const override
        {
            return *k;
        }
        cumulant_impl& op_incr() override
        {
            ++k;

            return *this;
        }
        cumulant_impl* clone() const override
        {
            return new cumulant_impl(k);
        }
    };

    // Copies of a cumulant.
    template<class S = double>
    class cumulant_copy {
        std::shared_ptr<sequence<S>> pk;
    public:
        cumulant_copy(const sequence<S>& s)
            : pk(s.clone())
        { }
        ~cumulant_copy()
        { }
        cumulant<S>* get() const
        {
            cumulant<S>* pc = dynamic_cast<cumulant<>*>(pk.get());
            if (pc == nullptr) {
                throw std::runtime_error("xll::cumulant_copy: dynamic cast failed");
            }
            
            return pc;
        }
        S operator()(const S& s) const
        {
            return (*get())(s);
        }
        operator bool() const
        {
            return *pk;
        }
        S operator*() const
        {
            return  *(*pk);
        }
        cumulant_copy& operator++()
        {
            ++(*pk);

            return *this;
        }
    };

}