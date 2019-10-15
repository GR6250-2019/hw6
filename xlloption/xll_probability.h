// xll_probability.h - Probability distributions for Excel
#pragma once
#include "xll_cumulant.h"

namespace xll {

	template<class X = double>
	struct probability {
		virtual ~probability()
		{ }
        X cdf(const X& x) const
        {
            return cdf_(x);
        }
        X pdf(const X& x) const
		{
			return pdf_(x);
		}
        X moment(const X& t) const
        {
            return moment_(t);
        }
        // Not really, but same interface.
        xll::cumulant<X>* moments() const
        {
            return moments_();
        }
        X cumulant(const X& s) const
		{
			return cumulant_(s);
		}
		xll::cumulant<X>* cumulants() const
		{
			return cumulants_();
		}
	private:
        virtual X cdf_(const X&) const = 0;
        virtual X pdf_(const X&) const = 0;
        virtual X moment_(const X&) const = 0;
        virtual xll::cumulant<X>* moments_() const = 0;
        virtual X cumulant_(const X&) const = 0;
		virtual xll::cumulant<X>* cumulants_() const = 0;
	};

	// inherit from P to provide implementation???
	template<class P, class X = double>
	class probability_impl : public probability<X> {
		P p;
	public:
		probability_impl(const P& p)
			: p(p)
		{ }
		~probability_impl()
		{ }
        X cdf_(const X& x) const override
        {
            return p.cdf(x);
        }
        X pdf_(const X& x) const override
		{
			return p.pdf(x);
		}
        X moment_(const X& t) const override
        {
            return p.moment(t);
        }
        xll::cumulant_impl<typename P::moments, X>* moments_() const override
        {
            return new cumulant_impl<P::moments>(P::moments(p));
        }

		X cumulant_(const X& x) const override
		{
			return p.cumulant(x);
		}
		xll::cumulant_impl<typename P::cumulants,X>* cumulants_() const override
		{
			return new cumulant_impl<P::cumulants>(P::cumulants(p));
		}
		
		
	};

}
