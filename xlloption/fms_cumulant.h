// fms_cumulant.h - A cumulant is a sequence of cumulants and operator() for the cumulant
#pragma once
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <valarray>
#include "fms_sequence.h"

namespace fms::cumulant {

    // K is cumulant sequence
    template<class K>
    using value_type = std::invoke_result_t<decltype(&K::operator*), K>;

    // Cumulants of a scalar multiple of a random variable.
    // kappa^{cX}_n = c^n kappa^X_n
    template<class K, class S = value_type<K>>
    class scale {
        K k;
        S c;
        S cn; // c^n
    public:
        scale(S c, K k)
            : k(k), c(c), cn(c)
        { }
        S operator()(S s) const 
        {
            return c * k(s);
        }
        operator bool() const
        {
            return k;
        }
        S operator*() const
        {
            return cn * (*k);
        }
        scale& operator++()
        {
            ++k;
            cn *= c;

            return *this;
        }
    };

    // Convert to mean 0, variance 1: X' = (X - mu)/sigma
    // kappa'_1 = kappa_1 - mu = 0, kappa'_2 = kappa_2/sigma^2 = 1, kappa_n' = kappa_n/sigma^n for n > 2.
    // Return original mean, standard, deviation, and normalized kappa_n, n >= 3.
    template<class K, class S = value_type<K>>
    inline auto normalize(K kappa)
    {
        S mean = *kappa;
        ++kappa;
        S variance = *kappa;
        ++kappa;

        S sigma = sqrt(variance);
        auto kappa3 = scale(1 / sigma, kappa) / sequence::constant(variance);

        return std::tuple(mean, sigma, kappa3);
    }

    template<size_t I, class S, class... Ks>
    constexpr auto tuple_sum_product(const std::valarray<S>& cn, const std::tuple<Ks...>& ks)
    {
        if constexpr (I == sizeof...(Ks) - 1) {
            return cn[I]*(*std::get<I>(ks));
        }
        else {
            return cn[I]*(*std::get<I>(ks)) + tuple_sum_product<I + 1>(cn, ks);
        }
    }

    template<size_t I, class S, class... Ks>
    constexpr S tuple_sum(const std::valarray<S>& c, const std::tuple<Ks...>& ks, const S& s)
    {
        if constexpr (I == sizeof...(Ks) - 1) {
            return c[I] * (std::get<I>(ks)(s));
        }
        else {
            return c[I] * (std::get<I>(ks)(s)) + tuple_sum<I + 1>(c, ks, s);
        }
    }

    template<size_t I, class... Ks>
    constexpr bool tuple_all(const std::tuple<Ks...>& ks)
    {
        if constexpr (I == sizeof...(Ks) - 1) {
            return std::get<I>(ks);
        }
        else {
            return std::get<I>(ks) && tuple_all<I + 1>(ks);
        }
    }

    // Linear combination of cumulants
    template<class ...Ks>
    class sum_product {
        using S = sequence::common_value_type<Ks...>;
        std::valarray<S> c;
        std::valarray<S> cn; // coefficients, c^n
        std::tuple<Ks...> ks;
    public:
        sum_product(const S* c, size_t n, std::tuple<Ks ...> ks)
            : c(c, n), cn(c, n), ks(ks)
        {
            if (n != std::tuple_size<std::tuple<Ks...>>::value) {
                throw std::invalid_argument("fms::cumulant::sum_product: coefficients and sequences must have the same size");
            }
        }
        sum_product(const S* c, size_t n, Ks ...ks)
            : sum_product(c, n, std::tuple<Ks...>(ks...))
        { }
        S operator()(const S& s) const
        {
            return tuple_sum<0>(c, ks, s);
        }
        operator bool() const
        {
            return tuple_all<0>(ks);
        }
        S operator*() const
        {
            return tuple_sum_product<0>(cn, ks);
        }
        sum_product& operator++()
        {
            cn *= c;
            std::apply([](auto& ...k) { (++k,...); }, ks);

            return *this;
        }
        sum_product& _(const S& s) const
        {
            auto ks_ = ks;
            std::apply([s](auto& ...k_) { (k_._(s),...); }, ks_);

            return sum_product(c, c.size(), ks_);
        }
    };

    // Cumulants of a constant random variable: c, 0, 0, ...
    template<class S = double>
    class constant {
        S c;
        size_t n = 0;
    public:
        constant(S c = 1)
            : c(c), n(0)
        { }
        S operator()(const S& s) const
        {
            return c * s;
        }
        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return n == 0 ? c : S(0);
        }
        constant& operator++() {
            ++n;

            return *this;
        }
    };

    // Cumulants of a normal random variable: mu, sigma^2, 0, ...
    template<class S = double>
    class normal {
        S mu;
        S sigma;
        size_t n;
    public:
        normal(S mu = 0, S sigma = 1)
            : mu(mu), sigma(sigma), n(0)
        { }
        // Normal cumulant
        S operator()(const S& s) const
        {
            return mu*s + sigma * sigma * s * s / 2;
        }
        operator bool() const
        {
            return true;
        }
        S operator*() const
        {
            return n == 0 ? mu : n == 1 ? sigma*sigma : 0;
        }
        normal& operator++()
        {
            ++n;

            return *this;
        }
        normal _(S s) const
        {
            return normal(mu + s, sigma);
        }
    };

    // Cumulants of a Poisson random variable: lambda, lambda, ....
    template<class S = double>
    class Poisson {
        S lambda;
    public:
        Poisson(S lambda = 0)
            : lambda(lambda)
        { }

        // Poisson cumulant.
        S operator()(const S& s) const
        {
            return lambda * (exp(s) - 1);
        }
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
        Poisson _(const S& s) const
        {
            return Poisson(exp(s) * lambda);
        }
    };

}
