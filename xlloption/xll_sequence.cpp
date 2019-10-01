// xll_sequence.cpp - Excel add-in for sequences
#include "../xll12/xll/xll.h"
#include "fms_sequence.h"

using namespace fms::sequence;
using namespace xll;

namespace xll {
    template<class X = double> // a sequence of X
    struct sequence {
        operator bool() const
        {
            return op_bool();
        }
        X operator*() const
        {
            return op_star();
        }
        sequence& operator++()
        {
            return op_plus();
        }
    private:
        virtual bool op_bool() const = 0;
        virtual X op_star() const = 0;
        virtual sequence<X>& op_plus() = 0;
    };
    template<class S, class X = double>
    class sequence_impl : public sequence<X> {
        S s;
    public:
        sequence_impl(S s)
            : s(s)
        { }
        bool op_bool() const override
        {
            return s;
        }
        X op_star() const override
        {
            return *s;
        }
        sequence_impl<S,X>& op_plus() override
        {
            ++s;

            return *this;
        }
    };
    template<class S>
    inline auto make_sequence_impl(S s)
    {
        return sequence_impl<S,double>(s);
    }
}

test test_sequence([] {

    iota i(0);
    auto msi = make_sequence_impl(iota(0.));
    auto si = sequence_impl(iota(0.));

    });



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

static AddIn xai_sequence_plus( //!!! change to incr
    Function(XLL_HANDLE, L"?xll_sequence_plus", L"XLL.SEQUENCE.INCR")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a sequence.")
    .Category(L"XLL")
    .FunctionHelp(L"Increment handle and return it. ")
);
HANDLEX WINAPI xll_sequence_plus(HANDLEX h)
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
