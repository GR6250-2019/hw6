// xll_cumulant.cpp - Excel add-in for cumulants.
#include <utility>
#include "../xll12/xll/xll.h"
#include "xll_sequence.h"
#include "xll_cumulant.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif

using namespace xll;
using namespace fms::cumulant;

static AddIn xai_cumulant_constant(
    Function(XLL_HANDLE, L"?xll_cumulant_constant", L"XLL.CUMULANT.CONSTANT")
    .Arg(XLL_DOUBLE, L"c", L"is the value of the constant random variable.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the cumulant of a constant random variable.")
);
HANDLEX WINAPI xll_cumulant_constant(double c)
{
#pragma XLLEXPORT
    return handle<sequence<>>(new cumulant_impl(constant(c))).get();
}

static AddIn xai_cumulant_normal(
    Function(XLL_HANDLE, L"?xll_cumulant_normal", L"XLL.CUMULANT.NORMAL")
    .Arg(XLL_DOUBLE, L"mu", L"is the mean. Default is 0.")
    .Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of the normal. Default is 1.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a normal cumulant.")
);
HANDLEX WINAPI xll_cumulant_normal(double mu, double sigma)
{
#pragma XLLEXPORT
    if (sigma == 0) {
        sigma = 1;
    }

    return handle<sequence<>>(new cumulant_impl(normal(mu, sigma))).get();
}

static AddIn xai_cumulant_Poisson(
    Function(XLL_HANDLE, L"?xll_cumulant_Poisson", L"XLL.CUMULANT.POISSON")
    .Arg(XLL_DOUBLE, L"lambda", L"is the Poisson mean parameter.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a Poisson cumulant.")
);
HANDLEX WINAPI xll_cumulant_Poisson(double lambda)
{
#pragma XLLEXPORT
    return handle<sequence<>>(new cumulant_impl(Poisson(lambda))).get();
}

static AddIn xai_cumulant(
    Function(XLL_DOUBLE, L"?xll_cumulant", L"XLL.CUMULANT")
    .Arg(XLL_HANDLE, L"k", L"is a handle to a cumulant.")
    .Arg(XLL_DOUBLE, L"s", L"is the value at which to calculate the cumulant.")
    .Category(CATEGORY)
    .FunctionHelp(L"Return the value of the cumulant at s.")
);
double WINAPI xll_cumulant(HANDLEX k, double s)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        handle<sequence<>> k_(k);
        cumulant<>* pk = dynamic_cast<cumulant<>*>(k_.ptr());
        ensure(pk != nullptr || !"failed to dynamic cast from sequence* to cumulant*");
        result = (*pk)(s);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

template<size_t... I>
auto make_sum_product(const double *c, const HANDLEX* h, std::index_sequence<I...>)
{
    auto t = std::tuple(cumulant_copy(*handle<sequence<>>(h[I]))...);

    return handle<sequence<>>(new cumulant_impl(sum_product(c, sizeof...(I), t))).get();
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

        sequence<>* ps;
        ps = handle<sequence<>>(ph->array[0]).ptr();
        auto pr = cumulant_copy<>(*ps);
        pr = pr;
        
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