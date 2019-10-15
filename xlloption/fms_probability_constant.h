// fms_probability_constant.h - Constant random variable.
#pragma once
#include <compare>
#include <limits>

namespace fms::probability {

	template<class X = double>
	class Constant {
		X c;
	public:
		Constant(const X c = X(0))
			: c(c)
		{ }
		const auto operator<=>(const Constant&) const = default;
		// Constant probability density function.
		X pdf(const X x) const
		{
			return x == c ? 1 : 0;
		}
		// Constant cumulative distribution function.
		X cdf(const X& x) const
		{
			return X(1) * (x >= c);
		}
		// Moment generating function: E exp(tX)
		X moment(const X& t) const
		{
			return exp(c*t);
		}
		class moments {
			friend class Constant<X>;
			Constant c;
			X cn; // c^n
		public:
			moments(const Constant<X>& c)
				: c(c), cn(1)
			{ }
			operator bool() const
			{
				return true;
			}
			X operator*() const
			{
				return cn;
			}
			moments& operator++()
			{
				cn *= c.c;

				return *this;
			}
            X operator()(const X& t) const
            {
                return c.moment(t);
            }
		};
		X cumulant(X s) const
		{
			return c * s;
		}
		class cumulants {
			friend class Constant<X>;
			Constant<X> c;
		public:
			cumulants(const Constant<X>& c)
				: c(c)
			{ }
			operator bool() const
			{
				return true;
			}
			X operator*() const
			{
				return c.c;
			}
			cumulants& operator++()
			{
				c.c = 0;

				return *this;
			}
            X operator()(const X& s) const
            {
                return c.cumulant(s);
            }
		};
		
	};

}
