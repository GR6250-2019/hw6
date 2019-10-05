// fms_Bell.h - Bell polynomials
#pragma once
#include "fms_sequence.h"

namespace fms {

    // Bell polynomials
    template<class K, class X = sequence::value_type<K>>
    class Bell {
        K kappa;
        std::vector<X> B; // cached values
        size_t n;
    public:
        Bell(K kappa)
            : kappa(kappa), B({ X(1) }), n(0)
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
            return B[n];
        }
        Bell& operator++()
        {
            using fms::sequence::choose;
            using fms::sequence::factorial;
            using fms::sequence::reverse;
            using fms::sequence::skip;
            using fms::sequence::sum;
            using fms::sequence::take;

            ++n;
            if (n >= B.size()) {
                // B_{n+1} = (sum_{k=0}^n C(n,k) B_{n-k} kappa_{k+1}
                auto Bnk = reverse(B.begin(), B.begin() += n);
                B.push_back(sum(choose(n - 1) * Bnk * skip(1, kappa)));
            }

            return *this;
        }

    };
    
    // Reduced Bell polynomials: b_n = B_n/n!
    template<class K, class X = sequence::value_type<K>>
    class bell {
        K kappa;
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
                // b_{n+1} = (sum_{k=0}^n b_{n-k} kappa_{k+1}/k!))/(n+1)
                auto bnk = reverse(b.begin(), b.begin() += n);
                b.push_back(sum(bnk * skip(1, kappa) / factorial<X>{}) / n);
            }
 
            return *this;
        }

    };

}
