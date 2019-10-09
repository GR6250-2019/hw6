// xll_black.cpp
#include "fms_black.h"
#include "xll_black.h"

using namespace xll;
using namespace fms::black;

test test_moneyness([]() {
	double f = 100;
	double sigma = 0.2;
	double k = 100;
	double t = 0.25;

	double z = moneyness(f, sigma*sqrt(t), k);
	ensure(z == (0.2 * 0.2 * 0.25 / 2) / (0.2 * sqrt(0.25)));
	
	double p = put(f, sigma, k, t);
	ensure(fabs(p - 3.987) < 0.001);

	double c = call(f, sigma, k, t);
	ensure(fabs(c - 3.987) < 0.001);

    f = 101;
    p = put(f, sigma, k, t);
    ensure(fabs(p - 3.5275) < 0.001);
    c = call(f, sigma, k, t);
    ensure(fabs(c - 4.5275) < 0.001);

	});

static AddIn xai_black_put(
	Function(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
	.Category(L"XLL")
	.FunctionHelp(L"Return Black put value.")
);
double WINAPI xll_black_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = put(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}
static AddIn xai_black_put_delta(
    Function(XLL_DOUBLE, L"?xll_black_put_delta", L"XLL.BLACK.PUT.DELTA")
    .Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
    .Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
    .Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
    .Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
    .Category(L"XLL")
    .FunctionHelp(L"Return Black put delta value.")
);
double WINAPI xll_black_put_delta(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        result = put_delta(f, sigma, k, t);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_black_vega(
    Function(XLL_DOUBLE, L"?xll_black_vega", L"XLL.BLACK.VEGA")
    .Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
    .Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
    .Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
    .Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
    .Category(L"XLL")
    .FunctionHelp(L"Return Black put delta value.")
);
double WINAPI xll_black_vega(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        result = vega(f, sigma, k, t);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

static AddIn xai_black_call(
    Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
    .Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
    .Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
    .Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
    .Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
    .Category(L"XLL")
    .FunctionHelp(L"Return Black call value.")
);
double WINAPI xll_black_call(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        result = call(f, sigma, k, t);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

test test_delta([]() {

    double f = 100;
    double sigma = .2;
    double k = 100;
    double t = 0.25;

    double p = put(f, sigma, k, t);

    for (double h : {.01, .001, .0001, 0.00001}) {
        double dp = put_delta(f, sigma, k, t);
        double p_ = put(f + h, sigma, k, t);
        double _p = put(f - h, sigma, k, t);
        double dp_ = (p_ - _p) / (2 * h);
        double gamma = (p_ - 2 * p + _p) / (h * h);
        //double a, b;
        //a = dp - dp_;
        //b = gamma * h * h / 2;
        ensure(fabs(dp - dp_) <= gamma*h*h/2);
    }

    });

test test_vega([]() {
    //!!! Implement a test for vega
    double f = 100;
    double sigma = .2;
    double k = 100;
    double t = 0.25;

    double p = put(f, sigma, k, t);

    for (double h : {.01, .001, .0001, 0.00001}) {
        double dp = vega(f, sigma, k, t);
        double p_ = put(f, sigma + h, k, t);
        double _p = put(f, sigma - h, k, t);
        double dp_ = (p_ - _p) / (2 * h);
        double gamma = (p_ - 2 * p + _p) / (h * h);
        double a, b;
        a = dp - dp_;
        b = gamma * h * h / 2;
        ensure(fabs(dp - dp_) <= -100 * gamma * h * h / 2);
    }

    });

//!!! Implement XLL.BLACK.PUT.IMPLIED(f, p, k, t) where p is the put value.

static AddIn xai_black_put_implied(
    Function(XLL_DOUBLE, L"?xll_black_put_implied", L"XLL.BLACK.PUT.IMPLIED")
    .Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
    .Arg(XLL_DOUBLE, L"p", L"is the put price.", L"3.987")
    .Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
    .Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
    .Category(L"XLL")
    .FunctionHelp(L"Return Black put_implied value.")
);
double WINAPI xll_black_put_implied(double f, double p, double k, double t)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        result = put_implied_volatility(f, p, k, t);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}
