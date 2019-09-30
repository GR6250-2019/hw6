// fms_Bell.h - Bell polynomials
#pragma once
#include "fms_sequence.h"

namespace fms {

    // b_{n+1}
    template<class K>
    class bell {
        K kappa;
        using X = decltype(*kappa);
        X b;
        size_t n;
        auto b_ = sequence::cache(bell(kappa));
    public:
        bell(K kappa)
            : kappa(sequence::concatenate(kappa, sequence::constant(X(0)))), b(1), n(0)
        { }
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return b;
        }
        // b_{n+1} = 1/(n + 1) sum_{k=0}^n b_{n-k} kappa_{k+1}/k!
        bell& operator++()
        {
            using fms::sequence::cache;
            using fms::sequence::factorial;
            using fms::sequence::reverse;
            using fms::sequence::skip;
            using fms::sequence::sum;
            using fms::sequence::take;

            ++n;
            auto b_ = cache(bell(kappa));
            b_ = skip(n - 1, b_);
            
            auto r = take(n - 1, reverse(b_));
            b = sum(r * skip(1, kappa));
            //b = sum(take(n-1,reverse(skip(n - 1, bell(kappa)))) * skip(1, kappa) / factorial<X>{});
            b /= n;

            return *this;
        }

    };

}
