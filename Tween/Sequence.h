#pragma once
#ifndef HT_TWEEN_SEQUENCE_H
#define HT_TWEEN_SEQUENCE_H

#include "Types.h"
#include "Transition.h"

namespace ht {
namespace tween {

    namespace sequence {

        typedef void (*GeneralFunction) ();

        class Base {
        protected:
            struct trans_t {
                double begin_ms;
                double end_ms;
                TransitionRef ref;
                GeneralFunction on_complete;
            };

            Vec<trans_t> transitions;
            bool b_repeat {false};
            bool b_auto_erase {false};
            double duration_ms {0.};
            double offset_ms {0.};
            int _current_index = 0;

        public:
            virtual ~Base() {}

            bool update(const double curr_ms) {
                if (transitions.empty()) return false;

                double ms = curr_ms - offset_ms;
                if (repeat()) {
                    ms = fmod(ms, duration_ms);
                }

                const size_t idx = from_time_to_index(ms);

                // Adding code to find any skipped indexes. This can happen if you set
                // a then() with a short amount of time and in the sketches internal loop has
                // a delay.
                if (int(idx) != _current_index) {
                  // index is stepping up. For example from 1 to 2.
                  // Note this may not work if the calls skip two tranisitons.
                  if (_current_index + 1 < int(idx)) {
                    // A trans_t vector has been skipped so let's call it to make sure it still executes.
                    if (transitions[idx - 2].on_complete) {
                      transitions[idx - 2].on_complete();
                    }
                  }
                  // call the previous on complete
                  if (transitions[idx - 1].on_complete) {
                    transitions[idx - 1].on_complete();
                  }
                  _current_index = int(idx);
                }

                if (idx >= transitions.size()) {
                    transitions.back().ref->update(transitions.back().end_ms);
                    return false;
                }

                transitions[idx].ref->update(ms - transitions[idx].begin_ms);
                return true;
            }

            double offset() const { return offset_ms; }
            double duration() const { return duration_ms; }
            double duration_with_offset() const { return duration_ms + offset_ms; }

            void auto_erase(const bool b) { b_auto_erase = b; }
            bool auto_erase() const { return b_auto_erase; }

            void repeat(const bool b) { b_repeat = b; }
            bool repeat() const { return b_repeat; }

            size_t size() const { return transitions.size(); }
            bool empty() const { return transitions.size() == 0; }
            void clear() { transitions.clear(); }

        protected:
            void add_transition(const trans_t& t) {
                transitions.emplace_back(t);
                transitions.shrink_to_fit();
                duration_ms = 0;
                for (const auto& t : transitions)
                    duration_ms += t.ref->duration();
            }

            size_t from_time_to_index(const double ms) const {
                if (ms < 0) return 0;
                for (size_t i = 0; i < transitions.size(); ++i)
                    if (transitions[i].end_ms > ms)
                        return i;
                return transitions.size();
            }
        };

        template <typename T>
        class Sequence : public Base {
            T& target;
            T prev_target;

        public:
            virtual ~Sequence() {}

            explicit Sequence(T& target)
            : target(target), prev_target(target) {}

            template <typename U = T>
            auto init(const U& to)
                -> typename std::enable_if<std::is_convertible<U, T>::value, Sequence<T>&>::type {
                prev_target = (T)to;
                return *this;
            }

            template <typename EasingType = Ease::Linear, typename U = T>
            auto then(const U& to, const double in = 0, GeneralFunction on_complete = NULL)
                -> typename std::enable_if<std::is_convertible<U, T>::value, Sequence<T>&>::type {
                add_transition(trans_t {duration(), duration() + in, std::make_shared<Transition<T, EasingType>>(target, prev_target, to, in), on_complete});
                prev_target = (T)to;
                return *this;
            }

            Sequence<T>& hold(const double in, GeneralFunction on_complete = NULL) {
                add_transition(trans_t {duration(), duration() + in, std::make_shared<Transition<T, Ease::Linear>>(target, prev_target, prev_target, in), on_complete});
                return *this;
            }

            Sequence<T>& offset(const double ms) {
                offset_ms = ms;
                return *this;
            }
        };

    }  // namespace sequence

    template <typename T>
    using Sequence = sequence::Sequence<T>;
    using SequenceRef = Ref<sequence::Base>;

}  // namespace tween
}  // namespace ht

#endif  // HT_TWEEN_SEQUENCE_H
