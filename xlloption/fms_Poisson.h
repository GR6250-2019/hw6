// fms_Poisson.h - Poisson distributiong
//  P(X = k) = exp(-lambda x) s^k/k!
#pragma once
#include <cmath>

namespace fms::Poisson {

    inline static double pdf(double x, double lambda)
    {
        double x_;
        if (x < 0 || 0 == modf(x, &x_)) {
            return 0;
        }
        double sk = 1; // s^k/k!
        for (double j = 1; j <= x; ++j) {
            sk *= x / j;
        }
        
        return exp(-lambda * x) * sk;
    }
    inline static double cdf(double x, double lambda)
    {
        double p = 0;
        double sk = 1; // s^k/k!
        for (double j = 1; j <= x; ++j) {
            sk *= x / j;
            p += sk;
        }

        return exp(-lambda * x) * p;
    }

}
