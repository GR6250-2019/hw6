// xll_cumlant.h - Cumulants for Excel
#pragma once
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
    template<class K, class S = fms::cumulant::value_type<K>>
    inline auto shift(cumulant_impl<K,S>& k, const S& s)
    {
        return shift(k, s);
    }

    // Copies of a cumulant.
    template<class S = double>
    class cumulant_copy {
        sequence<S>* pk;
    public:
        cumulant_copy(const sequence<S>& s)
            : pk(s.clone())
        { }

        cumulant_copy(const cumulant_copy& s)
            : pk(s.pk->clone())
        { }
        cumulant_copy& operator=(const cumulant_copy& s)
        {
            if (this != &s) {
                delete pk;
                pk = s.pk->clone();
            }

            return *this;
        }
        ~cumulant_copy()
        {
            delete pk;
        }
        S operator()(const S& s) const
        {
            cumulant<S>* pc = dynamic_cast<cumulant<>*>(pk);
            if (pc == nullptr) {
                throw std::runtime_error("xll::cumulant_copy: dynamic cast failed");
            }
            return (*pc)(s);
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