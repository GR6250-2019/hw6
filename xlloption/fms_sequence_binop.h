// fms_sequence_binop.h - binary operators on sequences
#pragma once
#include <compare>
#include <functional>
#include "fms_sequence_traits.h"

namespace fms::sequence {

    template<class Op, class S, class T>
    class binop {
        inline static Op op = Op{};
        S s;
        T t;
    public:
        binop(S s, T t)
            : s(s), t(t)
        { }
        const auto operator<=>(const binop&) const = default;
        operator bool() const
        {
            return s && t;
        }
        auto operator*() const
        {
            return op(*s, *t);
        }
        binop& operator++()
        {
            ++s;
            ++t;

            return *this;
        }

    };

}

template<class S, class T, class = fms::has_operator_bool<S>>
inline auto operator+(S s, T t)
{
    using X = std::common_type_t<decltype(*s), decltype(*t)>;

    return fms::sequence::binop<std::plus<X>, S, T>(s, t);
}
template<class S, class T>
inline auto operator-(S s, T t)
{
    using X = std::common_type_t<decltype(*s), decltype(*t)>;

    return fms::sequence::binop<std::minus<X>, S, T>(s, t);
}
template<class S, class T>
inline auto operator*(S s, T t)
{
    using X = std::common_type_t<decltype(*s), decltype(*t)>;

    return fms::sequence::binop<std::multiplies<X>, S, T>(s, t);
}
template<class S, class T>
inline auto operator/(S s, T t)
{
    using X = std::common_type_t<decltype(*s), decltype(*t)>;

    return fms::sequence::binop<std::divides<X>, S, T>(s, t);
}

