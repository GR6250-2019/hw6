// xll_option.cpp - European option pricing.
#include "../xll12/xll/xll.h"
#include "xll_cumulant.h"
#include "fms_option.h"

using namespace xll;
using namespace fms;

static AddIn xai_option_pdf(
    Function(XLL_DOUBLE, L"?xll_option_pdf", L"XLL.OPTION.PDF")
    .Arg(XLL_DOUBLE, L"x", L"is the value at which to evaluate the density function.")
    .Arg(XLL_HANDLE, L"kappa", L"is a handle to the cumulants of the random variable.")
    .Category(L"XLL")
    .FunctionHelp(L"Return the density function for the random variable having cumulants kappa at x.")
);
double WINAPI xll_option_pdf(double x, HANDLEX kappa)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        handle<xll::sequence<>> kappa_(kappa);
        xll::cumulant<>* pk = dynamic_cast<xll::cumulant<>*>(kappa_.ptr());

        result = option::pdf(x, cumulant_copy(*pk));
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_option_cdf(
    Function(XLL_DOUBLE, L"?xll_option_cdf", L"XLL.OPTION.CDF")
    .Arg(XLL_DOUBLE, L"x", L"is the value at which to evaluate the cumulative distribution function.")
    .Arg(XLL_HANDLE, L"kappa", L"is a handle to the cumulants of the random variable.")
    .Category(L"XLL")
    .FunctionHelp(L"Return the probability that the random variable having cumulants kappa is less than x.")
);
double WINAPI xll_option_cdf(double x, HANDLEX kappa)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        handle<xll::sequence<>> kappa_(kappa);

        result = option::cdf(x, sequence_copy(*kappa_));
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static Auto<OpenAfter> xao_test_option([]() {

    return TRUE;
    });