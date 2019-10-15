// fms_probability_beta.h - Beta distribution.
#pragma once
#include <cmath>
#include <stdexcept>
#include "fms_sequence.h"

namespace fms::probability {

	template<class X = double>
	class Beta {
		X alpha, beta;
	public:
		Beta(const X& alpha, const X& beta)
			: alpha(alpha), beta(beta)
		{
			if (alpha <= 0) {
				throw std::domain_error("fms::probability::Beta: alpha must be positive");
			}
			if (beta <= 0) {
				throw std::domain_error("fms::probability::Beta: beta must be positive");
			}
		}
		X pdf(const X& x) const
		{
			if (x <= 0 || x >= 1) {
				throw std::domain_error("fms::probability::Beta::pdf: x must be between 0 and 1");
			}

			using std::pow;
			using std::tgamma;

			X xa_ = pow(x, alpha - 1);
			X xb_ = pow(x, beta - 1);
			X Bab = tgamma(alpha) * tgamma(beta) / tgamma(alpha + beta);

			return  xa_ * xb_ / Bab;
		}
#pragma warning(push)
#pragma warning(disable: 4702)
        X cdf(const X& x) const
		{
			if (x <= 0 || x >= 1) {
				throw std::domain_error("fms::probability::Beta::pdf: x must be between 0 and 1");
			}

			throw std::domain_error("fms::probability::Beta::cdf: not implemented");
			return 0;
		}
#pragma warning(pop)
        // moment generating function: E exp(t X)
		X moment(const X& t, long n = 100) const
		{
			using fms::sequence::sum;
			using fms::sequence::epsilon;
			using fms::sequence::power;
			using fms::sequence::factorial;
			using fms::sequence::take;

			return sum(take(n, epsilon(moments(*this) * power(t) / factorial<X>())));
		}
		class moments {
			friend class Beta<X>;
			Beta<X> B;
			X a_b = 1;
			long n = 0;
		public:
			moments(const Beta<X>& B)
				: B(B)
			{ }
			moments(const X& alpha, const X& beta)
				: B(alpha, beta)
			{ }
			operator bool() const
			{
				return true;
			}
			X operator*() const
			{
				return a_b;
			}
			X operator++()
			{
				a_b *= (B.alpha + n) / (B.alpha + B.beta + n);
				++n;

				return *this;
			}
            X operator()(const X& t) const
            {
                return B.moment(t);
            }
        };
		X cumulant(const X& s) const
		{
			using std::log;

			return log(moment(s));
		}
		class cumulants {
            Beta<X> B;
		public:
			cumulants(const Beta& B)
                : B(B)
			{
				//throw std::runtime_error("fms::probability::Beta::cumulants: not implemented");
			}
			operator bool() const
			{
				return true;
			}
			// Use partial Bell polynomials???
			X operator*() const
			{
				return 0;
			}
			cumulants& operator++()
			{
				return *this;
			}
            X operator()(const X& s) const
            {
                return B.cumulant(s);
            }
		};
	};
}
