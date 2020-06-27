#pragma once
#ifndef HT_TWEEN_SEQUENCE_H
#define HT_TWEEN_SEQUENCE_H

#include "Types.h"
#include "Transition.h"

namespace ht {
namespace tween {

namespace sequence {

    struct Base
    {
        virtual ~Base() {}
        virtual bool update(const int32_t curr_ms) = 0;
        virtual uint32_t duration() const = 0;
    };


    template <typename T>
    class Sequence : public Base
    {
        struct trans_t
        {
            uint32_t begin_ms;
            uint32_t end_ms;
            TransitionRef ref;
        };

        T& target;
        T prev_target;
        Vec<trans_t> transitions;
        uint32_t duration_ms {0};

    public:

        virtual ~Sequence() {}

        explicit Sequence(T& target) : target(target), prev_target(target) {}

        template <typename EasingType = Ease::Linear, typename U = T>
        auto then(const U& to, const uint32_t in = 0)
        -> typename std::enable_if<std::is_convertible<U, T>::value, Sequence<T>&>::type
        {
            add_transition(trans_t{duration(), duration() + in, make_shared<Transition<T, EasingType>>(target, prev_target, to, in)});
            prev_target = (T)to;
            return *this;
        }

        Sequence<T>& wait(const uint32_t in)
        {
            add_transition(trans_t{duration(), duration() + in, make_shared<Transition<T, Ease::Linear>>(target, prev_target, prev_target, in)});
            return *this;
        }

        virtual bool update(const int32_t curr_ms) override
        {
            if (transitions.empty()) return false;

            const size_t idx = from_time_to_index(curr_ms);
            if (idx >= transitions.size())
            {
                transitions.back().ref->update(transitions.back().end_ms);
                return false;
            }

            transitions[idx].ref->update(curr_ms - transitions[idx].begin_ms);
            return true;
        }

        virtual uint32_t duration() const { return duration_ms; }

        size_t size() const { return transitions.size(); }
        bool empty() const { return transitions.size() == 0; }
        void clear() { transitions.clear(); }

    private:

        void add_transition(const trans_t& t)
        {
            transitions.emplace_back(t);
            duration_ms = 0;
            for (const auto& t : transitions)
                duration_ms += t.ref->duration();
        }

        size_t from_time_to_index(const int32_t ms) const
        {
            if (ms < 0) return 0;
            for (size_t i = 0; i < transitions.size(); ++i)
                if (transitions[i].end_ms > ms)
                    return i;
            return transitions.size();
        }

    };

} // sequence

template <typename T>
using Sequence = sequence::Sequence<T>;
using SequenceRef = Ref<sequence::Base>;

} // tween
} // ht

#endif // HT_TWEEN_SEQUENCE_H
