// xll_probability.h - Probability distributions for Excel
#pragma once
#include "xll_cumulant.h"

namespace xll {

	template<class X = double>
	struct probability {
		virtual ~probability()
		{ }
		X pdf(const X& x) const
		{
			return pdf_(x);
		}
		X cumulant(const X& s) const
		{
			return cumulant_(s);
		}
		/*
		xll::cumulant<X>& cumulants() const
		{
			return cumulants_();
		}
		*/
	private:
		virtual X pdf_(const X&) const = 0;
		virtual X cumulant_(const X&) const = 0;
		//virtual xll::cumulant<X>& cumulants_() const = 0;
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
		X pdf_(const X& x) const override
		{
			return p.pdf(x);
		}
		X cumulant_(const X& x) const override
		{
			return p.cumulant(x);
		}
		/*
		xll::cumulant_impl<P, X>& cumulants_() const override
		{
			return cumulant_impl(p.cumulants());
		}
		*/
		
	};

}
