// xll_option.cpp - European option pricing.
#include "../xll12/xll/xll.h"
#include "xll_cumulant.h"
#include "fms_option.h"

using namespace xll;
using namespace fms;

static AddIn xai_option(
    Document(L"xlloption")
    .Documentation(L"General option pricing.")
);

static AddIn xai_option_xll(
    Document(L"XLL")
    .Documentation(L"XLL documentation.")
);

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

        result = option::pdf(x, cumulant_copy(*kappa_));
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

static AddIn xai_option_put(
    Function(XLL_DOUBLE, L"?xll_option_put", L"XLL.OPTION.PUT")
    .Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
    .Arg(XLL_DOUBLE, L"s", L"is the volatility.", L"=0.2*0.25")
    .Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
    .Arg(XLL_HANDLE, L"kappa", L"is a handle to the cumulants of the random variable.")
    .Category(L"XLL")
    .FunctionHelp(L"Return the value of a put options having cumulants kappa at.")
);
double WINAPI xll_option_put(double f, double s, double k, HANDLEX kappa)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();    try {
        handle<xll::sequence<>> kappa_(kappa);
        //xll::cumulant<>* pk = dynamic_cast<xll::cumulant<>*>(kappa_.ptr());
        //ensure(pk != nullptr || !"xll_option_put: dynamic cast to cumulant failed");

        result = option::put(f, s, k, cumulant_copy(*kappa_));
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}


static Auto<OpenAfter> xao_test_option([]() {

    return TRUE;
    });