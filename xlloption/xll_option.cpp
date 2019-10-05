// xll_option.cpp - European option pricing.
#include "../xll12/xll/xll.h"
#include "xll_sequence.h"
#include "fms_option.h"

using namespace xll;
using namespace fms;

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

        return option::cdf(x, sequence_ref(*kappa_));
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}
