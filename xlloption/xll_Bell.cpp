// xll_Bell.cpp - Excel add-in for Bell polynomials
#include "xlloption.h"
#include "xll_sequence.h"
#include "fms_Bell.h"

using namespace fms;
using namespace xll;

static AddIn xai_Bell(
    Function(XLL_HANDLE, L"?xll_Bell", L"XLL.BELL")
    .Arg(XLL_HANDLE, L"x", L"is a handle to the sequence of coefficients.")
    .Arg(XLL_FP, L"init", L"is an array of initial values for the polynomial.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a sequence of Bell polynomials.")
    .Documentation(
        L"The Bell polynomials provide the relationship between the moments and cumulants of a random variable. "
    )
);
HANDLEX xll_Bell(HANDLEX x, _FP12* pB)
{
#pragma XLLEXPORT
    handlex h;

    try {
        if (pB->array[0] == 0) {
            pB->array[0] = 1;
        }
        handle<xll::sequence<>> x_(x);
        handle<xll::sequence<>> h_(new sequence_impl(Bell(sequence_copy(*x_), std::initializer_list<double>(begin(*pB), end(*pB)))));
        h = h_.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

static AddIn xai_bell(
    Function(XLL_HANDLE, L"?xll_bell", L"XLL.BELL.REDUCED")
    .Arg(XLL_HANDLE, L"x", L"is a handle to the sequence of coefficients.")
    .Arg(XLL_FP, L"init", L"is an array of initial values for the polynomial.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a sequence of reduced Bell polynomials.")
);
HANDLEX xll_bell(HANDLEX x, _FP12* pb)
{
#pragma XLLEXPORT
    handlex h;

    try {
        if (pb->array[0] == 0) {
            pb->array[0] = 1;
        }
        handle<xll::sequence<>> x_(x);
        handle<xll::sequence<>> h_(new sequence_impl(bell(sequence_copy(*x_), std::initializer_list<double>(begin(*pb), end(*pb)))));
        h = h_.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}
