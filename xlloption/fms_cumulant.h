// fms_cumulant.h - Cumulant and cumulants
#pragma once
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <valarray>
#include "fms_sequence.h"

namespace fms::cumulant {

    // Cumulants of a scalar multiple of a random variable.
    // kappa^{cX}_n = c^n kappa^X_n
    template<class S, class X = sequence::value_type<S>>
    class scale {
        S s;
        X c;
        X cn; // c^n
    public:
        scale(X c, S s)
            : s(s), c(c), cn(c)
        { }
        X operator()(X x) const 
        {
            return c * s(x);
        }
        operator bool() const
        {
            return s;
        }
        X operator*() const
        {
            return cn * (*s);
        }
        scale& operator++()
        {
            ++s;
            cn *= c;

            return *this;
        }
    };

    // Convert to mean 0, variance 1: X -> X' = (X - mu)/sigma
    // kappa'_1 = kappa_1 - mu = 0, kappa'_2 = kappa_2/sigma^2 = 1, kappa_n' = kappa_n/sigma^n for n > 2.
    // Return original mean, standard, deviation, and normalized kappa_n, n >= 3.
    template<class Kappa, class X = sequence::value_type<Kappa>>
    inline auto normalize(Kappa kappa)
    {
        X mean = *kappa;
        ++kappa;
        X variance = *kappa;
        ++kappa;

        X sigma = sqrt(variance);
        auto kappa3 = scale(1 / sigma, kappa) / sequence::constant(variance);

        return std::tuple(mean, sigma, kappa3);
    }

    template<size_t I, class X, class... Ss>
    constexpr auto tuple_sum_product(const std::valarray<X>& cn, const std::tuple<Ss...>& ss)
    {
        if constexpr (I == sizeof...(Ss) - 1) {
            return cn[I]*(*std::get<I>(ss));
        }
        else {
            return cn[I]*(*std::get<I>(ss)) + tuple_sum_product<I + 1>(cn, ss);
        }
    }

    template<size_t I, class X, class... Ss>
    constexpr X tuple_sum(const std::valarray<X>& c, const std::tuple<Ss...>& ss, X s)
    {
        if constexpr (I == sizeof...(Ss) - 1) {
            return c[I] * (std::get<I>(ss)(s));
        }
        else {
            return c[I] * (std::get<I>(ss)(s)) + tuple_sum<I + 1>(c, ss, s);
        }
    }

    // Linear combination of cumulants
    template<class ...Kappas>
    class sum_product {
        using X = sequence::common_value_type<Kappas...>;
        std::valarray<X> c;
        std::valarray<X> cn; // coefficients, c^n
        std::tuple<Kappas...> kappas;
    public:
        sum_product(const X* c, size_t n, const std::tuple<Kappas ...>& kappas)
            : c(c, n), cn(c, n), kappas(kappas)
        {
            if (n != std::tuple_size<std::tuple<Kappas...>>::value) {
                throw std::invalid_argument("fms::cumulant::sum_product: coefficients and sequences must have the same size");
            }
        }
        sum_product(const X* c, size_t n, Kappas ...kappas)
            : sum_product(c, n, std::tuple<Kappas...>(kappas...))
        { }
        X operator()(X s) const
        {
            return tuple_sum<0>(c, kappas, s);
        }
        operator bool() const
        {
            return true;
        }
        X operator*() const
        {
            return tuple_sum_product<0>(cn, kappas);
        }
        sum_product& operator++()
        {
            cn *= c;
            std::apply([](auto& ...kappa) { (++kappa,...); }, kappas);

            return *this;
        }
    };

    // 0, 1, 0, ...
    template<class S = double>
    class normal {
        size_t n;
    public:
        // Normal cumulant
        S operator()(S s) const
        {
            return s * s / 2;
        }
        normal()
            : n(0)
        { }
        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return S(n == 1);
        }
        normal& operator++()
        {
            ++n;

            return *this;
        }
    };

    // lambda, lambda, ....
    template<class S = double>
    class Poisson {
        S lambda;
    public:
        // Poisson cumulant.
        S operator()(S s) const
        {
            return lambda * (exp(s) - 1);
        }
        Poisson(S lambda = 0)
            : lambda(lambda)
        { }

        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return lambda;
        }
        Poisson& operator++()
        {
            return *this;
        }
    };

}
