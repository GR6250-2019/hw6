// fms_sequence_traits.h - Traits for sequences.
#pragma once
#include <type_traits>

namespace fms {

    // using IsSequence = ...
    template<class, class = void>
    struct has_operator_bool
        : std::false_type { };
    template<class S>
    struct has_operator_bool<S, std::void_t<decltype(std::declval<S>().operator bool())>>
        : std::true_type { };

}

