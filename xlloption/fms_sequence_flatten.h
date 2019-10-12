// fms_sequence_flatten.h - Reduce a sequence of sequences to a sequence.
#pragma once

namespace fms::sequence {

    template<class Ss>
    class flatten {
        Ss ss;
    public:
        flatten(Ss ss)
            : ss(ss)
        { }
        operator bool() const
        {
            return ss && *ss;
        }
        auto operator*() const
        {
            return **ss;
        }
        flatten& operator++()
        {
            if (ss) {
                if (*ss) {
                    ++*ss;
                }
                else {
                    ++ss;
                }
            }

            return *this;
        }
    };

}
