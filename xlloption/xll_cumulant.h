// xll_cumlant.h - Cumulants for Excel
#pragma once

namespace xll {

    template<class S = double>
    struct cumulant {
        virtual ~cumulant()
        { }
        S operator()(S s)
        {
            return op_value(s);
        }
        operator bool() const
        {
            return op_bool();
        }
        S operator*() const
        {
            return op_star();
        }
        cumulant& operator++()
        {
            return op_incr();
        }
    };

}