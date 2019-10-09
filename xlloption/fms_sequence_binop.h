// fms_sequence_binop.h - binary operators on sequences
#pragma once
#include <compare>
#include <functional>
#include "fms_sequence_traits.h"

namespace fms::sequence {

    template<class Op, class S, class T, class X = common_value_type<S, T>>
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
        X operator*() const
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
    template<class Op, class S, class T>
    inline auto make_binop(S s, T t)
    {
        return fms::sequence::binop<Op, S, T>(s, t);
    }

}


template<class S, class T, class X = fms::sequence::common_value_type<S, T>>
inline auto operator+(S s, T t)
{
    return fms::sequence::binop<std::plus<X>, S, T>(s, t);
}
template<class S, class T, class X = fms::sequence::common_value_type<S, T>>
inline auto operator-(S s, T t)
{
    return fms::sequence::binop<std::minus<X>, S, T>(s, t);
}
template<class S, class T, class X = fms::sequence::common_value_type<S, T>>
inline auto operator*(S s, T t)
{
    return fms::sequence::binop<std::multiplies<X>, S, T>(s, t);
}
template<class S, class T, class X = fms::sequence::common_value_type<S, T>>
inline auto operator/(S s, T t)
{
    return fms::sequence::binop<std::divides<X>, S, T>(s, t);
}

