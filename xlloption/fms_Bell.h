// fms_Bell.h - Bell polynomials
#pragma once
#include "fms_sequence.h"

namespace fms {

    // b_{n+1}
    template<class K>
    class bell {
        K kappa;
        using X = decltype(*kappa);
        std::vector<X> b; // cached values
        size_t n;
    public:
        bell(K kappa)
            : kappa(sequence::concatenate(kappa, sequence::constant(X(0)))), b({ X(1) }), n(0)
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
        // b_{n+1} = 1/(n + 1) sum_{k=0}^n b_{n-k} kappa_{k+1}/k!
        bell& operator++()
        {
            using fms::sequence::factorial;
            using fms::sequence::reverse;
            using fms::sequence::skip;
            using fms::sequence::sum;
            using fms::sequence::take;

            ++n;
            assert(n <= b.size());
            if (n == b.size()) {
                auto rnb = take(n, reverse(b.begin(), b.end()));
                b.push_back(sum(rnb * skip(1, kappa) / factorial<X>{})/n);
            }
 
            return *this;
        }

    };

}
