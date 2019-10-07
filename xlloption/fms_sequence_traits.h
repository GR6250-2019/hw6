// fms_sequence_traits.h - Traits for sequences.
#pragma once
#include <type_traits>

namespace fms::sequence {

    template<class X>
    using is_arithmetic = typename std::enable_if<std::is_arithmetic<X>::value>::type;

    template<class S>
    using value_type = std::invoke_result_t<decltype(&S::operator*), S>;

    template<class... S>
    using common_value_type = std::common_type_t<value_type<S>...>;
    
    // using IsSequence = ...
    template<class, class = void>
    struct has_operator_bool
        : std::false_type { };
    template<class S>
    struct has_operator_bool<S, std::void_t<decltype(std::declval<S>().operator bool())>>
        : std::true_type { };

}

