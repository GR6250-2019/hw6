// fms_cumulant.h - Cumlant and cumulants
#pragma once
#include <cmath>

namespace fms::cumulant {

    template<class S = double>
    struct normal {
        static S cumulant(S s)
        {
            return s * s / 2;
        }
        // 0, 1, 0, ...
        class cumulants {
            size_t n;
        public:
            cumulants()
                : n(0)
            { }
            operator bool() const
            {
                return true;
            }
            S operator*() const
            {
                return S(n == 1);
            }
            cumulants& operator++()
            {
                ++n;

                return *this;
            }
        };
    };

    template<class S = double>
    class Poisson {
        S lambda;
    public:
        Poisson(S lambda = 0)
            : lambda(lambda)
        { }

        S cumulant(S s)
        {
            return lambda*(exp(s) - 1);
        }
        static S cumulant(S s, S lambda_)
        {
            return lambda_ * (exp(s) - 1);
        }
        // lambda, lambda, ....
        class cumulants {
            S lambda;
        public:
            cumulants(S lambda = 0)
                : lambda(lambda)
            { }

            operator bool() const
            {
                return true;
            }
            S operator*() const
            {
                return lambda;
            }
            cumulants& operator++()
            {
                return *this;
            }
        };

    };

}
