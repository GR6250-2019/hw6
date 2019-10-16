// xll_normal.cpp
#include "fms_normal.h"
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif

using namespace xll;

static AddIn xai_normal_pdf(
    Function(XLL_DOUBLE, L"?xll_normal_pdf", L"XLL.NORMAL.PDF")
    .Arg(XLL_DOUBLE, L"x", L"is the value at which to compute the pdf.")
    .Arg(XLL_DOUBLE, L"mu", L"is the mean value of the normal random variable. Default is 0.")
    .Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of the normal random variable. Default is 1.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the value of the probability density function.")
    .Documentation(
        L"This function computes the probability density function "
        L"using the standard normal density "
        MATH_(L"e" SUP_(minus_ L"z" sup2_ L"/2") L"/" radic_ L"2" pi_)
    )
);
double WINAPI xll_normal_pdf(double x, double mu, double sigma)
{
#pragma XLLEXPORT
    if (sigma == 0) {
        sigma = 1;
    }

    return fms::normal::pdf(x, mu, sigma);
}

#ifdef _DEBUG

test test_normal_pdf([] {
    ensure(xll_normal_pdf(0, 0, 0) == 1 / M_SQRT2PI);
    ensure(xll_normal_pdf(0, 0, 2) == 1 / (2 * M_SQRT2PI));

    });

#endif

static AddIn xai_normal_cdf(
    Function(XLL_DOUBLE, L"?xll_normal_cdf", L"XLL.NORMAL.CDF")
    .Arg(XLL_DOUBLE, L"x", L"is the value at which to compute the cdf.")
    .Arg(XLL_DOUBLE, L"mu", L"is the mean value of the normal random variable. Default is 0.")
    .Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of the normal random variable. Default is 1.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the value of the cumulative distribution function.")
    .Documentation(
        L"This function computes the cumulative distribution function "
        MATH_(int_ SUB_(minus_ infin_) SUP_(L"x") L"e" SUP_(minus_ L"z" sup2_ L"/2") L" dx/" radic_ L"2" pi_)
    )
);
double WINAPI xll_normal_cdf(double x, double mu, double sigma)
{
#pragma XLLEXPORT
    if (sigma == 0) {
        sigma = 1;
    }

    return fms::normal::cdf(x, mu, sigma);
}

#ifdef _DEBUG

test test_normal_cdf([] {
    ensure(xll_normal_cdf(0, 0, 0) == 0.5);

    });

#endif

static AddIn xai_normal_inv(
    Function(XLL_DOUBLE, L"?xll_normal_inv", L"XLL.NORMAL.INV")
    .Arg(XLL_DOUBLE, L"x", L"is the value at which to compute the inverse.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the inverse of the cumulative distribution function.")
    .Documentation(
        L"This function computes the inverse of the cumulative distribution function "
        MATH_(int_ SUB_(minus_ infin_) SUP_(L"x") L"e" SUP_(minus_ L"z" sup2_ L"/2") L" dx/" radic_ L"2" pi_)
    )
);
double WINAPI xll_normal_inv(double x)
{
#pragma XLLEXPORT
    double p = std::numeric_limits<double>::quiet_NaN();

    try {
        p = fms::normal::inv(x);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return p;
}

#ifdef _DEBUG

test test_normal_inv([] {
    ensure(xll_normal_inv(0.5) == 0);

    });

#endif
