// fms_Bell.h - Bell polynomials
#pragma once
#include "fms_sequence.h"

namespace fms {

    // Reduced Bell polynomials: b_n = B_n/n!
    template<class K>
    class bell {
        K kappa;
        using X = decltype(*kappa);
        std::vector<X> b; // cached values
        size_t n;
    public:
        bell(K kappa)
            : kappa(kappa), b({ X(1) }), n(0)
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
            return b[n];
        }
        bell& operator++()
        {
            using fms::sequence::factorial;
            using fms::sequence::reverse;
            using fms::sequence::skip;
            using fms::sequence::sum;
            using fms::sequence::take;

            ++n;
            if (n >= b.size()) {
                // b_{n+1} = (sum_{k=0}^n b_{n-k} kappa_{k+1}/k))/(n+1)
                for (size_t m = b.size(); m <= n; ++m) {
                    auto rmb = take(m, reverse(b.begin(), b.end()));
                    b.push_back(sum(rmb * skip(1, kappa) / factorial<X>{}) / m);
                }
            }
 
            return *this;
        }

    };

}
