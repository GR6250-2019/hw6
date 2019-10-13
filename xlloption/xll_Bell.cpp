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
        L"They are defined by B" SUB_(L"0") L" = 1 and "
        PARA_(
            L"B" SUB_(L"n+1") L"(x" SUB_(L"1") L", ..., x" SUB_(L"n+1") L")"
            L" = " sum_ SUP_(L"n") SUB_(L"k = 0") L" C(n,k) B" SUB_(L"n-k")
            L"(x" SUB_(L"1") L", ..., x" SUB_(L"k") L") " kappa_ SUB_(L"k+1")
        )
        PARA_(
            L"where C(n,k) = n!/k!(n - k)! is the number of combinations choosing k items from n."
        )
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
