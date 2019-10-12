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

static AddIn xai_cumulant_constant(
    Function(XLL_HANDLE, L"?xll_cumulant_constant", L"XLL.CUMULANT.CONSTANT")
    .Arg(XLL_DOUBLE, L"c", L"is the value of the constant random variable.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to the cumulant of a constant random variable.")
    .Documentation(
        L"The cumulants of a constant are c, 0, 0, ..."
    )
);
HANDLEX WINAPI xll_cumulant_constant(double c)
{
#pragma XLLEXPORT
    return handle<sequence<>>(new cumulant_impl(fms::cumulant::constant(c))).get();
}

static AddIn xai_cumulant_normal(
    Function(XLL_HANDLE, L"?xll_cumulant_normal", L"XLL.CUMULANT.NORMAL")
    .Arg(XLL_DOUBLE, L"mu", L"is the mean. Default is 0.")
    .Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of the normal. Default is 1.")
    .Arg(XLL_DOUBLE, L"scale", L"is a scalar multiple to apply to the cumulant. Default is 1.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a scaled normal cumulant.")
    .Documentation(
        L"The cumulant is " MATH_(kappa_ L"(s) = " mu_ L"s + " sigma_ sup2_ L" s" sup2_ L"/2.")
    )
);
HANDLEX WINAPI xll_cumulant_normal(double mu, double sigma, double c)
{
#pragma XLLEXPORT
    if (sigma == 0) {
        sigma = 1;
    }
    if (c == 0) {
        c = 1;
    }

    return handle<sequence<>>(new cumulant_impl(Normal(mu, sigma, c))).get();
}

static AddIn xai_cumulant_poisson(
    Function(XLL_HANDLE, L"?xll_cumulant_poisson", L"XLL.CUMULANT.POISSON")
    .Arg(XLL_DOUBLE, L"lambda", L"is the Poisson mean parameter.")
    .Arg(XLL_DOUBLE, L"scale", L"is a scalar multiple to apply to the cumulant. Default is 1.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return a handle to a scaled Poisson cumulant.")
    .Documentation(
        L"The cumulant is " MATH_(kappa_ L"(s) = " lambda_ L"(exp(x) - 1).")
    )
);
HANDLEX WINAPI xll_cumulant_poisson(double lambda, double c)
{
#pragma XLLEXPORT
    if (c == 0) {
        c = 1;
    }

    return handle<sequence<>>(new cumulant_impl(Poisson(lambda, c))).get();
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
static AddIn xai_cumulant_normalize(
    Function(XLL_FP, L"?xll_cumulant_normalize", L"XLL.CUMULANT.NORMALIZE")
    .Arg(XLL_HANDLE, L"k", L"is a handle to a cumulant.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Return the mean, variance, and handle to remaining cumulant.")
);
_FP12* WINAPI xll_cumulant_normalize(HANDLEX k)
{
#pragma XLLEXPORT
    static xll::FP12 result(3, 1);

    try {
        handle<sequence<>> k_(k);
        cumulant<>* pk = dynamic_cast<cumulant<>*>(k_.ptr());
        ensure(pk != nullptr || !"failed to dynamic cast from sequence* to cumulant*");
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

BOOL WINAPI xll_sequence_bool(HANDLEX);
double WINAPI xll_sequence_star(HANDLEX);
HANDLEX WINAPI xll_sequence_incr(HANDLEX);
HANDLEX WINAPI xll_sequence_copy(HANDLEX);

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
    .Arg(XLL_FP, L"handles", L"is an array of handles to a cumulants.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Returns a handle to the sum of the cumulants.")
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

