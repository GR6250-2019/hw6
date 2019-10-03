// fms_sequence_choose.h - C(n,k) = n!/(n - k)!k! for k = 0, ..., n
#pragma once

namespace fms::sequence {

    template<class X = double>
    class choose {
        X n, k, Cnk; // n choose k
    public:
        choose(X n)
            : n(n), k(0), Cnk(1)
        { }
        operator bool() const
        {
            return k <= n;
        }
        X operator*() const
        {
            return Cnk;
        }
        choose& operator++()
        {
            Cnk *= n - k;
            Cnk /= ++k;

            return *this;
        }
    };

}
