// xll_Hermite.cpp - Add-in for Hermite polynomials
#include "fms_Hermite.h"
#include "fms_sequence_copy.h"
#include "fms_sequence_take.h"
#include "xlloption.h"
#include "xll_sequence.h"

using namespace xll;
using namespace fms;

static AddIn xai_Hermite(
    Function(XLL_HANDLE, L"?xll_Hermite", CATEGORY L".HERMITE")
    .Arg(XLL_DOUBLE, L"x", L"is the value at which to compute the polynomials.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return the first n values of the Hermite polynomials.")
    .Documentation(
        L"The Hermite polynomials are defined by " MATH_(L"H" SUB_(L"0") L"(x) = 1, ")
        MATH_(L"H" SUB_(L"1") L"(x) = x") L", and "
        PARA_(
        MATH_(L"H" SUB_(L"n+1") L" = x H" SUB_(L"n") L" " minus_ L" n H" SUB_(L"n-1") L"(x)")
        L" for " MATH_(L"n " ge_ L"2") L"."
        )
    )
);
HANDLEX WINAPI xll_Hermite(double x)
{
#pragma XLLEXPORT
    handlex h;

    try {
        handle<xll::sequence<>> h_(new sequence_impl(Hermite(x)));
        h = h_.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());

        return 0;
    }

    return h;
}