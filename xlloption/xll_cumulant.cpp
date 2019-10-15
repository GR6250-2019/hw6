// xll_cumulant.cpp - Excel add-in for cumulants.
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include "fms_cumulant.h"
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"
#include "xll_sequence.h"
#include "xll_cumulant.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif

using namespace xll;
using namespace fms::cumulant;

static AddIn xai_cumulant_normalize(
    Function(XLL_FP, L"?xll_cumulant_normalize", L"XLL.CUMULANT.NORMALIZE")
    .Arg(XLL_HANDLE, L"k", L"is a handle to a cumulant.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return the mean, variance, and handle to remaining cumulant.")
    .Documentation(
        L"Convert to a cumulants with mean 0 and variance 1. "
        L"Return the original mean and standard deviation, and a handle to the remaining normalized cumulants. "
    )
);
_FP12* WINAPI xll_cumulant_normalize(HANDLEX k)
{
#pragma XLLEXPORT
    static xll::FP12 result(3, 1);

    try {
        handle<sequence<>> k_(k);
        auto [mu, sigma, kappa3] = normalize(cumulant_copy(*k_));
        result[0] = mu;
        result[1] = sigma;
        result[2] = handle<sequence<>>(new sequence_impl(kappa3)).get();

    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result.get();
}
static AddIn xai_cumulant_scale(
    Function(XLL_HANDLE, L"?xll_cumulant_scale", L"XLL.CUMULANT.SCALE")
    .Arg(XLL_HANDLE, L"handle", L"is handle to a cumulant.")
    .Arg(XLL_DOUBLE, L"scale", L"is the scalar multiplier of the corresponding random variable.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to a scaled cumulant.")
    .Documentation(
        L"Return a handle to a scaled cumulant. "
    )
);

HANDLEX WINAPI xll_cumulant_scale(HANDLEX k, double c)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> k_(k);

        result = handle<sequence<>>(new cumulant_impl(scale(cumulant_copy(*k_), c))).get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

BOOL WINAPI xll_sequence_bool(HANDLEX);
double WINAPI xll_sequence_star(HANDLEX);
HANDLEX WINAPI xll_sequence_incr(HANDLEX);
HANDLEX WINAPI xll_sequence_copy(HANDLEX);
HANDLEX WINAPI xll_cumulant(HANDLEX, double);

class cumulant_sum {
    size_t n;
    std::vector<HANDLEX> h;
    void copy()
    {
        std::for_each(h.begin(), h.end(), [](HANDLEX& hi) { hi = xll_sequence_copy(hi);  });
    }
public:
    cumulant_sum(size_t n, const HANDLEX* h_)
        : n(n), h(h_, h_ + n)
    {
        copy();
    }
    cumulant_sum(const cumulant_sum& cs)
        : n(cs.n), h(cs.h)
    {
        copy();
    }
    cumulant_sum& operator=(const cumulant_sum& cs)
    {
        if (this != &cs) {
            n = cs.n;
            h = cs.h;
            copy();
        }

        return *this;
    }
    ~cumulant_sum()
    { }
    operator bool() const
    {
        return std::all_of(h.begin(), h.end(), [](HANDLEX hi) { return xll_sequence_bool(hi); });
    }
    double operator*() const
    {
        return std::accumulate(h.begin(), h.end(), 0., [](double s, HANDLEX hi) { return s + xll_sequence_star(hi); });
    }
    cumulant_sum& operator++()
    {
        std::for_each(h.begin(), h.end(), [](HANDLEX hi) { xll_sequence_incr(hi);  });
        return *this;
    }
    double operator()(double s) const
    {
        return std::accumulate(h.begin(), h.end(), 0., [s](double x, HANDLEX hi) { 
            return x + xll_cumulant(hi, s); });
    }
};


static AddIn xai_cumulant_sum(
    Function(XLL_HANDLE, L"?xll_cumulant_sum", L"XLL.CUMULANT.SUM")
    .Arg(XLL_FP, L"handles", L"is an array of handles to cumulants.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Return a handle to the sum of the cumulants.")
    .Documentation(
        L"Return a handle to the sum of the cumulants. "
    )
);
HANDLEX WINAPI xll_cumulant_sum(const _FP12* cs)
{
#pragma XLLEXPORT
    handlex result;

    try {
        handle<sequence<>> h(new cumulant_impl(cumulant_sum(size(*cs), cs->array)));
        result = h.get();
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

