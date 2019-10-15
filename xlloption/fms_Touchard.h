// fms_Touchard.h - Touchard polynomials
// T_{n+1}(x) = x sum_{k=0}^n C(n, k) T_k(x)
// Use T_n(x) = Bell(x,...,x)???
#pragma once
#include "fms_sequence.h"

namespace fms {

	// Touchard polynomials
	template<class X = double>
	class Touchard {
		std::vector<X> T; // cached values
		X x;
		size_t n;
	public:
		Touchard(const X& x)
			: T({ 1 }), x(x), n(0)
		{ }
		void reset()
		{
			n = 0;
		}
		operator bool() const
		{
			return true;
		}
		X operator*() const
		{
			return T[n];
		}
		Touchard& operator++()
		{
			using fms::sequence::choose;
			using fms::sequence::factorial;
			using fms::sequence::sum;
			using fms::sequence::make_iterator;

			++n;
			if (n >= T.size()) {
				// T_{n+1}(x) = x sum_{k=0}^n C(n, k) T_k(x)
				T.push_back(x*sum(choose(X(n - 1)) * make_iterator(T)));
			}

			return *this;
		}

	};

}
