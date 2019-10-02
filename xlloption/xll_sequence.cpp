// xll_sequence.cpp - Excel add-in for sequences
#include "../xll12/xll/xll.h"
#include "xll_sequence.h"

using namespace fms::sequence;
using namespace xll;

static AddIn xai_sequence_bool(
    Function(XLL_BOOL, L"?xll_sequence_bool", L"XLL.SEQUENCE.BOOL")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Return whether a sequence can be dereferrenced.")
);
BOOL WINAPI xll_sequence_bool(HANDLEX h)
{
#pragma XLLEXPORT
    BOOL result = FALSE;

    try {
        handle<xll::sequence<double>> h_(h);
        result = !!(*h_);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_star(
    Function(XLL_DOUBLE, L"?xll_sequence_star", L"XLL.SEQUENCE.STAR")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Return the current sequence value.")
);
double WINAPI xll_sequence_star(HANDLEX h)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        handle<xll::sequence<double>> h_(h);
        result = *(*h_);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_incr( //!!! change to incr
    Function(XLL_HANDLE, L"?xll_sequence_incr", L"XLL.SEQUENCE.INCR")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Increment handle and return it. ")
);
HANDLEX WINAPI xll_sequence_incr(HANDLEX h)
{
#pragma XLLEXPORT
    try {
        handle<xll::sequence<double>> h_(h);
        ++(*h_);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

static AddIn xai_sequence_take(
    Function(XLL_FP, L"?xll_sequence_take", L"XLL.SEQUENCE.TAKE")
    .Arg(XLL_WORD, L"count", L"is then number of items to take from the handle.")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Returns the next count rows from the sequence.")
);
_FP12* WINAPI xll_sequence_take(WORD n, HANDLEX h)
{
#pragma XLLEXPORT
    static xll::FP12 result;

    try {
        handle<xll::sequence<double>> h_(h);
        result.resize(n, 1);
        copy(take(n, sequence_ref(*h_)), result.begin());
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result.get();
}

static AddIn xai_sequence_iota(
    Function(XLL_HANDLE, L"?xll_sequence_iota", L"XLL.SEQUENCE.IOTA")
    .Arg(XLL_DOUBLE, L"start", L"is the starting value for iota. Default is 0.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to the sequence start, start + 1, ...")
);
HANDLEX WINAPI xll_sequence_iota(double start)
{
#pragma XLLEXPORT
    handlex h;

    handle<xll::sequence<double>> h_ = new xll::sequence_impl(iota(start));
    h = h_.get();

    return h;
}

static AddIn xai_sequence_pow(
    Function(XLL_HANDLE, L"?xll_sequence_pow", L"XLL.SEQUENCE.POW")
    .Arg(XLL_DOUBLE, L"x", L"is the number whos powers form the sequence.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to the sequence 1, x, x^2, ...")
);
HANDLEX WINAPI xll_sequence_pow(double x)
{
#pragma XLLEXPORT
    handlex h;

    handle<xll::sequence<double>> h_ = new xll::sequence_impl(power(x));
    h = h_.get();

    return h;
}
