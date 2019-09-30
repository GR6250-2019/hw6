// fms_Hermite.h - Hermite polynomials
#pragma once

namespace fms {

    template<class X = double>
    class Hermite {
        X x;
        X _H, H, H_;
        size_t n;
    public:
        Hermite(X x)
            : x(x), _H(1), H(x), H_(x*x - 1), n(0)
        { }
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return n == 0 ? _H : n == 1 ? H : H_; // H_n(x)
        }
        // H_{n+1}(x) = x H_n(x) - n H_{n-1}(x);
        Hermite& operator++()
        {
            if (n > 1) {
                _H = H;
                H  = H_;
                H_ = x * H - X(n) * _H;
            }
            ++n;

            return *this;
        }
    };
}