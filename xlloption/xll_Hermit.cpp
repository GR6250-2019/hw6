// xll_Hermite.cpp - Add-in for Hermite polynomials
#include "fms_Hermite.h"
#include "fms_sequence_copy.h"
#include "fms_sequence_take.h"
#include "xlloption.h"

using namespace xll;
using namespace fms;

static AddIn xai_Hermite(
    Function(XLL_FP, L"?xll_Hermite", CATEGORY L".HERMITE")
    .Arg(XLL_WORD, L"n", L"is the number of polynomial values to return.")
    .Arg(XLL_DOUBLE, L"x", L"is the value at which to compute the polynomials.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the first n values of the Hermite polynomials.")
);
_FP12* WINAPI xll_Hermite(WORD n, double x)
{
#pragma XLLEXPORT
    static xll::FP12 result;

    try {
        result.resize(n, 1);
        Hermite H(x);
        sequence::copy(sequence::take(n, H), result.begin());
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());

        return 0;
    }

    return result.get();
}