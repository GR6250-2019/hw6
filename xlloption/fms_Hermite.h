// fms_Hermite.h - Hermite polynomials
// H_0(x) = 1, H_1(x) = x, H_{n + 1}(x) = x H_n(x) - n H_{n-1}(x)
#pragma once

namespace fms {

    template<class X = double>
    class Hermite {
        const X x;
        X _H, Hn, H_;
        size_t n;
    public:
        Hermite(const X x)
            : x(x), _H(1), Hn(x), H_(x*x - 1), n(0)
        { }
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return n == 0 ? X(1) : n == 1 ? x : H_; // H_n(x)
        }
        // H_{n+1}(x) = x H_n(x) - n H_{n-1}(x);
        Hermite& operator++()
        {
            if (n > 1) {
                _H = Hn;
                Hn = H_;
                H_ = x * Hn - X(n) * _H;
            }
            ++n;

            return *this;
        }
    };
}