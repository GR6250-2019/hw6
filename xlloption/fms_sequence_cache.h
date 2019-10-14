// fms_sequence_cache.h - Cache a sequence
#pragma once
#include <compare>
#include <vector>
#include "fms_sequence_traits.h"

namespace fms::sequence {

    template<class S, class X = value_type<S>, class C = std::vector<X>>
    struct cache {
        S s;
        mutable C s_;
        size_t n; // current index into cache
    public:
        cache(S s)
            : s(s), n(0)
        { }
        bool operator==(const cache& c) const
        {
            return n == c.n && s == c.s && std::equal(s_.begin(), s_.end(), c.s_.begin(), c.s_.end());
        }
        bool operator!=(const cache& c) const
        {
            return !operator==(c);
        }
        size_t size() const
        {
            return s_.size();
        }
        void reset(size_t n_ = 0)
        {
            n = n_;
        }
        void clear()
        {
            s_.clear();
        }
        const auto& buffer() const
        {
            return s_;
        }
        operator bool() const
        {
            return s || n < s_.size();
        }
        auto& operator*() const
        {
            if (n < s_.size()) {
                return s_[n];
            }

            s_.push_back(*s);
            
            return s_.back();
        }
        auto& operator[](size_t i) const
        {
            return s_[i];
        }
        cache& operator++()
        {
            ++s;
            if (s && n < s_.size()) {
                s_.push_back(*s);
            }
            ++n;

            return *this;
        }
        cache& operator--()
        {
            if (n > 0) {
                --n;
            }

            return *this;
        }
    };

}
