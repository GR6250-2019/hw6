// xll_sequence.cpp - Excel add-in for sequences
#include "fms_sequence.h"
#include "xll_sequence.h"
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"

using namespace fms::sequence;
using namespace xll;

#ifndef CATEGORY
#define CATEGORY L"Sequence"
#endif 

static AddIn xai_sequence(
    Document(CATEGORY)
    .Category(CATEGORY)
    .Documentation(
        PARA_(
            L"A sequence is a potentially infinite list of values. "
            L"It terminates when " C_(L"BOOL") L" returns false. "
            L"The current value is " C_(L"STAR") L". "
            L"The sequence moves to the next value when " C_(L"INCR") L" is called. "
            L"The latter is a dangerous function to call in Excel "
            L"because it modifies the underlying sequence "
            L"and breaks the Excel Zen of being purely functional. "
            L"Other sequence functions make copies of the sequence and "
            L"respect the Zen of Excel. "
        )
        PARA_(
            L"Create sequences with " C_(L"CONSTANT") L", " C_(L"FACTORIAL") L", " C_(L"IOTA") L", " C_(L"LIST") L", and " C_(L"POWER") L". "
            L"Combine sequences with " C_(L"ADD") L", " C_(L"SUB") L", " C_(L"MUL") L", and " C_(L"DIV") L" to perform "
            L"arithmetic operations. "
            L"Use " C_(L"CONCATENATE") L" to combine one sequence with another. "
        )
        PARA_(
            L"Use " C_(L"TAKE(n, sequence)") L" to see the first n values of a sequence. "
            L"Use " C_(L"SUM(sequence)") L" to add up all the values in a sequence. "
            L"Use " C_(L"EPSILON(sequence)") L" to truncate the sequence when the values "
            L"are smaller than machine epsilon. "
            L"Use " C_(L"LENGTH(sequence)") L" to find out how many elements there are. "
        )
    )
);


static AddIn xai_sequence_bool(
    Function(XLL_BOOL, L"?xll_sequence_bool", L"XLL.SEQUENCE.BOOL")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return whether a sequence can be dereferrenced.")
    .Documentation(
        L"Call the correponding " C_(L"operator bool() const") L" for the sequence. "
    )
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
    .Category(CATEGORY)
    .FunctionHelp(L"Return the current sequence value.")
    .Documentation(
        L"Call the correponding " C_(L"operator*() const") L" for the sequence. "
    )
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
    .Category(CATEGORY)
    .FunctionHelp(L"Increment handle and return it. ")
    .Documentation(
        L"Call the correponding " C_(L"operator++() const") L" for the sequence. "
    )
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

static AddIn xai_sequence_copy(
    Function(XLL_HANDLE, L"?xll_sequence_copy", L"XLL.SEQUENCE.COPY")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Copy a handle and return a new handle to it. ")
    .Documentation(
        L"Make a copy of a sequence and return the new handle. "
    )
);
HANDLEX WINAPI xll_sequence_copy(HANDLEX h)
{
#pragma XLLEXPORT
    handlex k_;

    try {
        handle<sequence<>> h_(h);
        handle<sequence<>> k((*h_).clone());
 
        k_ = k.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return k_;
}

//
// Arithmetic
//

static AddIn xai_sequence_add(
    Function(XLL_HANDLE, L"?xll_sequence_add", L"XLL.SEQUENCE.ADD")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_HANDLE, L"t", L"is a handle to a sequence.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the sum of two sequences. ")
    .Documentation(
        L"Return a handle to the sum of two sequences. "
    )
);
HANDLEX WINAPI xll_sequence_add(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(sequence_impl(sequence_copy<>(*s_) + sequence_copy<>(*t_)).clone());
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
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the difference of two sequences. ")
    .Documentation(
        L"Return a handle to the difference of two sequences. "
    )
);
HANDLEX WINAPI xll_sequence_sub(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(sequence_impl(sequence_copy<>(*s_) - sequence_copy<>(*t_)).clone());
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
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the product of two sequences. ")
    .Documentation(
        L"Return a handle to the product of two sequences. "
    )
);
HANDLEX WINAPI xll_sequence_mul(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(sequence_impl(sequence_copy<>(*s_) * sequence_copy<>(*t_)).clone());
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
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the quotient of two sequences. ")
    .Documentation(
        L"Return a handle to the quotient of two sequences. "
    )
);
HANDLEX WINAPI xll_sequence_div(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(sequence_impl(sequence_copy<>(*s_) / sequence_copy<>(*t_)).clone());
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

static AddIn xai_sequence_concatenate(
    Function(XLL_HANDLE, L"?xll_sequence_concatenate", L"XLL.SEQUENCE.CONCATENATE")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_HANDLE, L"t", L"is a handle to a sequence.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a sequence concatenating s followed by t.")
    .Documentation(
        L"Return a handle to the concatenation of two sequences. "
    )
);
HANDLEX WINAPI xll_sequence_concatenate(HANDLEX s, HANDLEX t)
{
#pragma XLLEXPORT
    handlex u_;

    try {
        handle<sequence<>> s_(s);
        handle<sequence<>> t_(t);
        handle<sequence<>> u(new sequence_impl(concatenate(sequence_copy(*s_), sequence_copy(*t_))));
        u_ = u.get();
    }

    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return u_;
}
static AddIn xai_sequence_constant(
    Function(XLL_HANDLE, L"?xll_sequence_constant", L"XLL.SEQUENCE.CONSTANT")
    .Arg(XLL_DOUBLE, L"c", L"is the value of the sequence.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a sequence that is constant. ")
    .Documentation(
        L"Return a handle to a sequence that is constant. "
    )
);
HANDLEX WINAPI xll_sequence_constant(double c)
{
#pragma XLLEXPORT
        return handle<sequence<>>(new sequence_impl(constant(c))).get();
 }


static AddIn xai_sequence_epsilon(
    Function(XLL_HANDLE, L"?xll_sequence_epsilon", L"XLL.SEQUENCE.EPSILON")
    .Arg(XLL_HANDLE, L"s", L"is a handle to a sequence.")
    .Arg(XLL_DOUBLE, L"scale", L"is the scale to use for machine epsilon. Default is 1.")
    .Arg(XLL_LONG, L"min", L"is the minimum number of terms to take. Default is 0.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a sequence that is truncated when x + scale == scale.")
    .Documentation(
        L"The sequence ends when the values are less than machine epsilon relative to scale. "
        L"Use scale &lt; 0 to terminate at floating point 0. "
    )
);
HANDLEX WINAPI xll_sequence_epsilon(HANDLEX h, double scale, LONG min)
{
#pragma XLLEXPORT
    handlex s_;

    try {
        if (scale == 0) {
            scale = 1;
        }
        else if (scale < 0) {
            scale = 0;
        }
        handle<sequence<>> h_(h);
        handle<sequence<>> s(new sequence_impl(epsilon(sequence_copy(*h_), scale, min)));
        s_ = s.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return s_;
}

static AddIn xai_sequence_factorial(
    Function(XLL_HANDLE, L"?xll_sequence_factorial", L"XLL.SEQUENCE.FACTORIAL")
    .Arg(XLL_DOUBLE, L"x", L"is the number whos factorials form the sequence. Default is 0. ")
    .Arg(XLL_LONG, L"n", L"is the integer increment to use for Pochhammer sequences. Default is 1.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the sequence of factorials 1 = 0!, 1 = 1!, 2 = 2! ...")
    .Documentation(
        L"If n is not 0 then the Pochhammer sequence is returned. "
        L"Use n = -1 to generate the falling Pochhammer sequence. "
    )
);
HANDLEX WINAPI xll_sequence_factorial(double x, LONG n)
{
#pragma XLLEXPORT
    if (n == 0)
        n = 1;

    return handle<sequence<>>(new sequence_impl(factorial(x, n))).get();
}

static AddIn xai_sequence_iota(
    Function(XLL_HANDLE, L"?xll_sequence_iota", L"XLL.SEQUENCE.IOTA")
    .Arg(XLL_DOUBLE, L"start", L"is the starting value for iota. Default is 0.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the sequence start, start + 1, ...")
    .Documentation(
        L"Return a handle to a counter. "
    )
);
HANDLEX WINAPI xll_sequence_iota(double start)
{
#pragma XLLEXPORT

    return handle<sequence<>>(new sequence_impl(iota(start))).get();
}

static AddIn xai_sequence_list(
    Function(XLL_HANDLE, L"?xll_sequence_list", L"XLL.SEQUENCE.LIST")
    .Arg(XLL_FP, L"array", L"is a array of numbers to use for a sequence.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a sequence of array values.")
    .Documentation(
        L"Return a handle to a sequence of array values. "
    )
);
HANDLEX WINAPI xll_sequence_list(const _FP12* pa)
{
#pragma XLLEXPORT
    handlex s_;

    try {
        handle<sequence<>> s(new sequence_impl(list(size(*pa), pa->array)));
        s_ = s.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return s_;
}

static AddIn xai_sequence_power(
    Function(XLL_HANDLE, L"?xll_sequence_power", L"XLL.SEQUENCE.POWER")
    .Arg(XLL_DOUBLE, L"x", L"is the number whos powers form the sequence.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the sequence of powers of x. ")
    .Documentation(
        L"Return a handle to the sequence of powers of the number " MATH_(L"x") L": "
        L"1, x, x" sup2_ ", x" sup3_ L", ..."
    )
);
HANDLEX WINAPI xll_sequence_power(double x)
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
    .Category(CATEGORY)
    .FunctionHelp(L"Return the length of the sequence.")
    .Documentation(
        L"Return the length of a sequence. "
    )
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
    .Category(CATEGORY)
    .FunctionHelp(L"Returns the sum of the sequence. ")
    .Documentation(L"Returns the sum of the sequence. ")
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
	.Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Returns the first count items from the sequence.")
    .Documentation(
        L"Take elements from a sequence. "
    )
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
        
        result.resize(n, 1);
        RW m = static_cast<RW>(copy(take(n, sequence_copy(*handle<sequence<>>(h))), result.begin()));
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