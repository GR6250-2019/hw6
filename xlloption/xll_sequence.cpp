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
        handle<sequence<>> h_(h);
        result = (*h_);
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
        handle<sequence<>> h_(h);
        result = *(*h_);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_incr(
    Function(XLL_HANDLE, L"?xll_sequence_incr", L"XLL.SEQUENCE.INCR")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Increment handle and return it. ")
);
HANDLEX WINAPI xll_sequence_incr(HANDLEX h)
{
#pragma XLLEXPORT
    try {
        handle<sequence<>> h_(h);
        ++(*h_);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

//
// Arithmetic
//

static AddIn xai_sequence_add(
    Function(XLL_HANDLE, L"?xll_sequence_add", L"XLL.SEQUENCE.ADD")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_HANDLE, L"t", L"is a handle to a sequence.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to the sum of two sequences. ")
);
HANDLEX WINAPI xll_sequence_add(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(sequence_impl(sequence_copy(*s_) + sequence_copy(*t_)).clone());
        result = u.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_sub(
    Function(XLL_HANDLE, L"?xll_sequence_sub", L"XLL.SEQUENCE.SUB")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_HANDLE, L"t", L"is a handle to a sequence.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to the difference of two sequences. ")
);
HANDLEX WINAPI xll_sequence_sub(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(sequence_impl(sequence_copy(*s_) - sequence_copy(*t_)).clone());
        result = u.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_mul(
    Function(XLL_HANDLE, L"?xll_sequence_mul", L"XLL.SEQUENCE.MUL")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_HANDLE, L"t", L"is a handle to a sequence.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to the product of two sequences. ")
);
HANDLEX WINAPI xll_sequence_mul(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(sequence_impl(sequence_copy(*s_) * sequence_copy(*t_)).clone());
        result = u.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_div(
    Function(XLL_HANDLE, L"?xll_sequence_div", L"XLL.SEQUENCE.DIV")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_HANDLE, L"t", L"is a handle to a sequence.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to the quotient of two sequences. ")
    );
    HANDLEX WINAPI xll_sequence_div(HANDLEX s, HANDLEX t)
    {
#pragma XLLEXPORT
        handlex result;

        try {
            handle<sequence<>> s_(s);
            handle<sequence<>> t_(t);
            handle<sequence<>> u(sequence_impl(sequence_copy(*s_) / sequence_copy(*t_)).clone());
            result = u.get();
        }
        catch (const std::exception & ex) {
            XLL_ERROR(ex.what());
        }

        return result;
    }

//
// Uncalced functions
//

static AddIn xai_sequence_epsilon(
    Function(XLL_HANDLE, L"?xll_sequence_epsilon", L"XLL.SEQUENCE.EPSILON")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_DOUBLE, L"one", L"is the scale to use for machine epsilon. Default is 0.")
    .Arg(XLL_LONG, L"min", L"is the minimum number of terms to take. Default is 0.")
    .Arg(XLL_LONG, L"max", L"is the maximum number of terms to take. Default is infinity.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a sequence that is truncated when x + one == one.")
);
HANDLEX WINAPI xll_sequence_epsilon(HANDLEX h, double one, LONG min, LONG max)
{
#pragma XLLEXPORT
    handlex s_;

    try {
        if (max == 0) {
            max = std::numeric_limits<LONG>::max();
        }
        handle<sequence<>> h_(h);
        handle<sequence<>> s(new sequence_impl(epsilon(sequence_copy(*h_), one, min, max)));
        s_ = s.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return s_;
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

    return handle<sequence<>>(new sequence_impl(iota(start))).get();
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

    return handle<sequence<>>(new sequence_impl(power(x))).get();
}

//
// Pure functions
//

static AddIn xai_sequence_length(
    Function(XLL_DOUBLE, L"?xll_sequence_length", L"XLL.SEQUENCE.LENGTH")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Returns the length of the sequence.")
);
double WINAPI xll_sequence_length(HANDLEX h)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        result = static_cast<double>(length(sequence_copy<>(*handle<sequence<>>(h))));
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_sum(
    Function(XLL_DOUBLE, L"?xll_sequence_sum", L"XLL.SEQUENCE.SUM")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Returns the sum of the sequence.")
);
double WINAPI xll_sequence_sum(HANDLEX h)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        result = static_cast<double>(sum(sequence_copy<>(*handle<sequence<>>(h))));
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_sequence_take(
    Function(XLL_FP, L"?xll_sequence_take", L"XLL.SEQUENCE.TAKE")
    .Arg(XLL_LONG, L"count", L"is then number of items to take from the handle.")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Returns the next count rows from the sequence.")
);
_FP12* WINAPI xll_sequence_take(LONG n, HANDLEX h)
{
#pragma XLLEXPORT
    static xll::FP12 result;

    try {
        if (n == 0) {
            return 0;
        }
        if (n < 0) {
            n = -n; // take reverse!!!
        }
        sequence_copy<> h_(*handle<sequence<>>(h));
        result.resize(n, 1);
        LONG m = copy(take(n, h_), result.begin());
        ensure(m <= n);
        if (m < n) {
            result.resize(m, 1);
        }
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
        
        return 0;
    }

    return result.get();
}


#ifdef _DEBUG

int test_sequence()
{
    //_crtBreakAlloc = 25177;
    auto si = sequence_impl(iota{});
    auto si2(si);
    si = si2;
    ensure(si);
    ensure(*si == 0);
    ++si;
    ensure(*si == 1);
    ensure(*si2 == 0);

    handle<sequence<>> h(new sequence_impl(iota{}));
    HANDLEX h_ = h.get();
    auto hs = handle<sequence<>>(h_);
    auto hp = sequence_copy<>(*hs);
    ensure(hp);
    ensure(*hp == 0);
    ++hp;
    ensure(*hp == 1);
    
    return TRUE;
}
Auto<OpenAfter> xoa_test_sequence(test_sequence);

#endif // _DEBUG