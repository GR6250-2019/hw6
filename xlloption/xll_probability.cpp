// xll_probability.cpp - Probability objects
#include "fms_probabilty.h"
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"
#include "xll_probability.h"

#ifndef CATEGRORY
#define CATEGORY L"XLL"
#endif

using namespace xll;
using namespace fms::probability;

static AddIn xai_probability_beta(
	Function(XLL_HANDLE, L"?xll_probability_beta", L"XLL.PROBABILITY.BETA")
	.Arg(XLL_DOUBLE, L"alpha", L"is first parameter.")
	.Arg(XLL_DOUBLE, L"beta", L"is the second parameter.")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"Return a handle to a beta distribution.")
	.Documentation(
		L"The cumulants of a beta random variable are ..."
		L"The cumulant is ..."
	)
);
HANDLEX WINAPI xll_probability_beta(double alpha, double beta)
{
#pragma XLLEXPORT
	handlex result;

	try {
		handle<probability<>> h(new probability_impl(Beta(alpha, beta)));
		result = h.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

static AddIn xai_probability_constant(
	Function(XLL_HANDLE, L"?xll_probability_constant", L"XLL.PROBABILITY.CONSTANT")
	.Arg(XLL_DOUBLE, L"c", L"is the value of the constant random variable.")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"Return a handle to a constant random variable.")
	.Documentation(
		L"The cumulants of a constant are c, 0, 0, ... "
		L"The cumulant is " MATH_(kappa_ L"(s) = cs. ")
	)
);
HANDLEX WINAPI xll_probability_constant(double c)
{
#pragma XLLEXPORT
	return handle<probability<>>(new probability_impl(Constant(c))).get();
}

static AddIn xai_probability_normal(
	Function(XLL_HANDLE, L"?xll_probability_normal", L"XLL.PROBABILITY.NORMAL")
	.Arg(XLL_DOUBLE, L"mu", L"is the mean. Default is 0.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of the normal. Default is 1.")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"Return a handle to a normal distribution.")
	.Documentation(
		L"The cumulants of a normal random variable are " mu_ L", " sigma_ SUP_(L"2") L", 0, 0 ... "
		L"The cumulant is " MATH_(kappa_ L"(s) = " mu_ L"s + " sigma_ sup2_ L" s" sup2_ L"/2.")
	)
);
HANDLEX WINAPI xll_probability_normal(double mu, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0) {
		sigma = 1;
	}

	return handle<probability<>>(new probability_impl(Normal(mu, sigma))).get();
}

static AddIn xai_probability_poisson(
	Function(XLL_HANDLE, L"?xll_probability_poisson", L"XLL.probability.POISSON")
	.Arg(XLL_DOUBLE, L"lambda", L"is the Poisson mean parameter.")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"Return a handle to a scaled Poisson probability.")
	.Documentation(
		L"The cumulants of a Poisson random variable are constant and equal to " lambda_ L". "
		L"The cumulant is " MATH_(kappa_ L"(s) = " lambda_ L"(e" SUP_(L"s") L" - 1).")
	)
);
HANDLEX WINAPI xll_probability_poisson(double lambda)
{
#pragma XLLEXPORT

	return handle<probability<>>(new probability_impl(Poisson(lambda))).get();
}

static AddIn xai_probability_cumulant(
	Function(XLL_DOUBLE, L"?xll_probability_cumulant", L"XLL.PROBABILITY.CUMULANT")
	.Arg(XLL_HANDLE, L"k", L"is a handle to a probability object.")
	.Arg(XLL_DOUBLE, L"s", L"is the value at which to calculate the cumulant.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the cumulant at s.")
	.Documentation(
		L"Evaluate the cumulant at a value. "
	)
);
double WINAPI xll_probability_cumulant(HANDLEX k, double s)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		handle<probability<>> k_(k);

		result = k_->cumulant(s);
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}
