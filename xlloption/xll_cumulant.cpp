// xll_cumulant.cpp - Excel add-in for cumulants.
#include "../xll12/xll/xll.h"
#include "xll_sequence.h"
#include "fms_cumulant.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif

using namespace xll;
using namespace fms::cumulant;

static AddIn xai_cumulant_normal(
    Function(XLL_DOUBLE, L"?xll_cumulant_normal", L"XLL.CUMULANT.NORMAL")
    .Arg(XLL_DOUBLE, L"s", L"is the value at which to calculate the normal cumulant.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the value of the normal cumulant.")
);
double WINAPI xll_cumulant_normal(double s)
{
#pragma XLLEXPORT
    return normal<>::cumulant(s);
}

static AddIn xai_cumulants_normal(
    Function(XLL_HANDLE, L"?xll_cumulants_normal", L"XLL.CUMULANTS.NORMAL")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the sequence of normal cumulants.")
);
double WINAPI xll_cumulants_normal()
{
#pragma XLLEXPORT
    return handle<sequence<>>(new sequence_impl(normal<>::cumulants())).get();
}

static AddIn xai_cumulant_Poisson(
    Function(XLL_DOUBLE, L"?xll_cumulant_Poisson", L"XLL.CUMULANT.POISSON")
    .Arg(XLL_DOUBLE, L"s", L"is the value at which to calculate the Poisson cumulant.")
    .Arg(XLL_DOUBLE, L"lambda", L"is the Poisson mean parameter.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the value of the Poisson cumulant.")
);
double WINAPI xll_cumulant_Poisson(double s, double lambda)
{
#pragma XLLEXPORT
    return Poisson<>::cumulant(s, lambda);
}

static AddIn xai_cumulants_Poisson(
    Function(XLL_HANDLE, L"?xll_cumulants_Poisson", L"XLL.CUMULANTS.POISSON")
    .Arg(XLL_DOUBLE, L"lambda", L"is the Poisson mean parameter.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the sequence of Poisson cumulants.")
);
double WINAPI xll_cumulants_Poisson(double lambda)
{
#pragma XLLEXPORT
    return handle<sequence<>>(new sequence_impl(Poisson<>::cumulants(lambda))).get();
}

static AddIn xai_cumulant_sum_product(
    Function(XLL_HANDLE, L"?xll_cumulant_sum_product", L"XLL.CUMULANT.SUM.PRODUCT")
    .Arg(XLL_FP, L"coefficients", L"is an array of weights to use for the cumulants.")
    .Arg(XLL_FP, L"handles", L"is an array of handles to cumulant sequences.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a sequence that is a linear combination of cumulants.")
);
HANDLEX WINAPI xll_cumulant_sum_product(_FP12* pc, _FP12* ph)
{
#pragma XLLEXPORT
    handlex h;

    try {
        ensure(size(*pc) == size(*ph));

        // scaled cumulant i
        auto ch = [pc,ph](WORD i) {
            return scale(pc->array[i], sequence_ref(*handle<sequence<>>(ph->array[i])));
        };
        auto hs = [](auto s) { 
            return handle<sequence<>>(new sequence_impl(s)).get(); 
        };

        auto n = size(*pc);
        if (n == 1) {
            return hs(ch(0));
        }
        if (n == 2) {
            return hs(ch(0)+ch(1));
        }
        if (n == 3) {
            return hs(ch(0) + ch(1) + ch(2));
        }
        if (n == 4) {
            return hs(ch(0) + ch(1) + ch(2) + ch(3));
        }
        if (n == 5) {
            return hs(ch(0) + ch(1) + ch(2) + ch(3) + ch(4));
        }
        if (n == 6) {
            return hs(ch(0) + ch(1) + ch(2) + ch(3) + ch(4) + ch(5));
        }
        if (n == 7) {
            return hs(ch(0) + ch(1) + ch(2) + ch(3) + ch(4) + ch(5) + ch(6));
        }
        if (n == 8) {
            return hs(ch(0) + ch(1) + ch(2) + ch(3) + ch(4) + ch(5) + ch(6) + ch(7));
        }
        if (n == 9) {
            return hs(ch(0) + ch(1) + ch(2) + ch(3) + ch(4) + ch(5) + ch(6) + ch(7) + ch(8));
        }

    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}