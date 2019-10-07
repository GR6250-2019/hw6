// xll_cumulant.cpp - Excel add-in for cumulants.
#include <utility>
#include "../xll12/xll/xll.h"
#include "xll_sequence.h"
#include "fms_cumulant.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif

using namespace xll;
using namespace fms::cumulant;

static AddIn xai_cumulant_constant(
    Function(XLL_DOUBLE, L"?xll_cumulant_constant", L"XLL.CUMULANT.constant")
    .Arg(XLL_DOUBLE, L"s", L"is the value at which to calculate the constant cumulant.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the value of the constant cumulant.")
);
double WINAPI xll_cumulant_constant(double s)
{
#pragma XLLEXPORT
    return constant<>()(s);
}

static AddIn xai_cumulants_constant(
    Function(XLL_HANDLE, L"?xll_cumulants_normal", L"XLL.CUMULANTS.CONSTANT")
    .Arg(XLL_DOUBLE, L"c", L"is the constant value (mean) of the random variable.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the sequence of cumulants for a constant random variable.")
);
double WINAPI xll_cumulants_constant(double c)
{
#pragma XLLEXPORT
    return handle<sequence<>>(new sequence_impl(constant<>(c))).get();
}

static AddIn xai_cumulant_normal(
    Function(XLL_DOUBLE, L"?xll_cumulant_normal", L"XLL.CUMULANT.NORMAL")
    .Arg(XLL_DOUBLE, L"s", L"is the value at which to calculate the normal cumulant.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the value of the normal cumulant.")
);
double WINAPI xll_cumulant_normal(double s)
{
#pragma XLLEXPORT
    return normal<>()(s);
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
    return handle<sequence<>>(new sequence_impl(normal<>())).get();
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
    return Poisson<>(lambda)(s);
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
    return handle<sequence<>>(new sequence_impl(Poisson<>(lambda))).get();
}

template<size_t... I>
auto make_sum_product(const double *c, const HANDLEX* h, std::index_sequence<I...>)
{
    auto t = std::tuple(sequence_copy(*handle<sequence<>>(h[I]))...);

    return handle<sequence<>>(new sequence_impl(sum_product(c, sizeof...(I), t))).get();
}

static AddIn xai_cumulant_sum_product(
    Function(XLL_HANDLE, L"?xll_cumulant_sum_product", L"XLL.CUMULANTS.SUM.PRODUCT")
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
//    _crtBreakAlloc = 26200;
    try {
        ensure(size(*pc) == size(*ph));

        auto n = size(*pc);
        if (n == 1) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<1>{});
        }
        if (n == 2) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<2>{});
        }
        if (n == 3) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<3>{});
        }
        if (n == 4) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<4>{});
        }
        if (n == 5) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<5>{});
        }
        if (n == 6) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<6>{});
        }
        if (n == 7) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<7>{});
        }
        if (n == 8) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<8>{});
        }
        if (n == 9) {
            return make_sum_product(pc->array, ph->array, std::make_index_sequence<9>{});
        }

    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}