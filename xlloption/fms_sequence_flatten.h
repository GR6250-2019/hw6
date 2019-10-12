// fms_sequence_flatten.h - Reduce a sequence of sequences to a sequence.
// {{a, a, ...},{b, b, ...},...} -> {a, a, ..., b, b, ...}
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
            if (ss && *ss) {
                ++(*ss);
                if (!*ss) {
                    ++ss;
                }
            }

            return *this;
        }
    };

}
