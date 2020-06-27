#pragma once
#ifndef HT_TWEEN_TRANSITION_H
#define HT_TWEEN_TRANSITION_H

#include "Types.h"
#include "util/Easing/Easing.h"

struct CRGB;
struct CHSV;

namespace ht {
namespace tween {

namespace transition
{
    struct Base
    {
        virtual ~Base() {}
        virtual bool update(const int32_t t) = 0;
        virtual int32_t duration() const = 0;
    };


    template <typename T, typename EasingType>
    class Transition : public Base
    {
        T& ref;
        const T from;
        const T to;
        const T diff;
        const int32_t duration_ms;
        EasingFunc<EasingType> ease;

    public:

        Transition(T& target, const T& from, const T& to, const int32_t in)
        : ref(target)
        , from(from)
        , to(to)
        , diff(to - from)
        , duration_ms(in)
        {
        }

        virtual ~Transition() {}

        virtual bool update(const int32_t t) override
        {
            if (t < 0)
                ref = from;
            else if (t >= duration_ms)
                ref = to;
            else
            {
                ref = lerp(t);
                return true;
            }
            return false;
        }

        virtual int32_t duration() const { return duration_ms; }

    private:

        template <typename U = T>
        auto lerp(const float t)
        -> typename std::enable_if<
            !std::is_same<U, CRGB>::value && !std::is_same<U, CHSV>::value,
            U
        >::type
        {
            return diff * ease.get((float)t / (float)duration_ms) + from;
        }

        template <typename U = T>
        auto lerp(const float t)
        -> typename std::enable_if<
            std::is_same<U, CRGB>::value || std::is_same<U, CHSV>::value,
            U
        >::type
        {
            float rgb[3];
            const float rate = ease.get((float)t / (float)duration_ms);
            for (size_t i = 0; i < 3; ++i)
                rgb[i] = ((float)to[i] - (float)from[i]) * rate + (float)from[i];
            return U(rgb[0], rgb[1], rgb[2]);
        }
    };

} // transition

template <typename T, typename EasingType>
using Transition = transition::Transition<T, EasingType>;
using TransitionRef = Ref<transition::Base>;

} // tween
} // ht

#endif // HT_TWEEN_TRANSITION_H
