// xll_Bell.cpp - Excel add-in for Bell polynomials
#include "xlloption.h"
#include "xll_sequence.h"
#include "fms_Bell.h"

using namespace fms;
using namespace xll;

static AddIn xai_Bell(
    Function(XLL_HANDLE, L"?xll_Bell", L"XLL.BELL")
    .Arg(XLL_HANDLE, L"x", L"is a handle to the sequence of coefficients.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a sequence of Bell polynomials.")
);
HANDLEX xll_Bell(HANDLEX x)
{
#pragma XLLEXPORT
    handlex h;

    try {
        handle<xll::sequence<>> x_(x);
        handle<xll::sequence<>> h_(new sequence_impl(Bell(sequence_copy(*x_))));
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
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a sequence of reduced Bell polynomials.")
);
HANDLEX xll_bell(HANDLEX x)
{
#pragma XLLEXPORT
    handlex h;

    try {
        handle<xll::sequence<>> x_(x);
        handle<xll::sequence<>> h_(new sequence_impl(bell(sequence_copy(*x_))));
        h = h_.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}
