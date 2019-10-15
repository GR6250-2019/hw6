// fms_Touchard.t.cpp - Test Touchard polynomials.
#include <cassert>
#include "fms_Touchard.h"
#include "fms_Bell.h"
#include "fms_sequence_constant.h"
#include "fms_sequence_equal.h"
#include "fms_sequence_take.h"

using namespace fms;

template<class X>
int test_fms_touchard()
{
	using sequence::take;
	using sequence::equal;

	X x = 0;
	auto T = Touchard(x);
	auto B = Bell(sequence::constant(x));
	long n = 10;
	auto Tn = take(n, T);
	auto Bn = take(n, B);
	assert(equal(Tn, Bn));

	return 0;
}
int test_fms_touchard_double = test_fms_touchard<double>();