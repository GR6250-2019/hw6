// fms_Bell.h - Bell polynomials
#pragma once

namespace fms {

    // b_{n+1}
    template<class K>
    class bell {
        using X = decltype(*K);
        K kappa;
        X b;
        size_t n;
    public:
        bell(K kappa)
            : kappa(kappa), b(1), n(0)
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
            using fms::sum;
            using fms::reverse;
            using fms::skip;
            using fms::factorial;

            ++n;
            //b = sum(sequence(n-1,reverse(bell(kappa))) * skip(1, kappa) / factorial{});
            b /= n;

            return *this;
        }

    };

}
