// fms_sequence_item.h - A sequence with one element.
#pragma once
#include "fms_sequence_list.h"

namespace fms::sequence {

    template<class X>
    inline auto item(X x)
    {
        return list({ x });
    }

}
