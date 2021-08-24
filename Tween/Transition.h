#pragma once
#ifndef HT_TWEEN_TRANSITION_H
#define HT_TWEEN_TRANSITION_H

#include "Types.h"
#include "util/Easing/Easing.h"

struct CRGB;
struct CHSV;

namespace ht {
namespace tween {

    namespace transition {
        struct Base {
            virtual ~Base() {}
            virtual bool update(const double t) = 0;
            virtual double duration() const = 0;
        };

        template <typename T, typename EasingType>
        class Transition : public Base {
            T& ref;
            const T from;
            const T to;
            const T diff;
            const double duration_ms;
            EasingFunc<EasingType> ease;

        public:
            Transition(T& target, const T& from, const T& to, const double in)
            : ref(target)
            , from(from)
            , to(to)
            , diff(to - from)
            , duration_ms(in) {
            }

            virtual ~Transition() {}

            virtual bool update(const double t) override {
                if (t < 0)
                    ref = from;
                else if (t >= duration_ms)
                    ref = to;
                else {
                    ref = lerp(t);
                    return true;
                }
                return false;
            }

            virtual double duration() const override { return duration_ms; }

        private:
            template <typename U = T>
            auto lerp(const double t)
                -> typename std::enable_if<
                    !std::is_same<U, CRGB>::value && !std::is_same<U, CHSV>::value,
                    U>::type {
                return diff * ease.get(t / duration_ms) + from;
            }

            template <typename U = T>
            auto lerp(const double t)
                -> typename std::enable_if<
                    std::is_same<U, CRGB>::value || std::is_same<U, CHSV>::value,
                    U>::type {
                double rgb[3];
                const double rate = ease.get(t / duration_ms);
                for (size_t i = 0; i < 3; ++i)
                    rgb[i] = ((double)to[i] - (double)from[i]) * rate + (double)from[i];
                return U(rgb[0], rgb[1], rgb[2]);
            }
        };

    }  // namespace transition

    template <typename T, typename EasingType>
    using Transition = transition::Transition<T, EasingType>;
    using TransitionRef = Ref<transition::Base>;

}  // namespace tween
}  // namespace ht

#endif  // HT_TWEEN_TRANSITION_H
