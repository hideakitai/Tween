#pragma once
#ifndef HT_TWEEN_EASING_TYPES_H
#define HT_TWEEN_EASING_TYPES_H

#include "EasingBase.h"

namespace ht {
namespace ease {

    struct BackIn {};
    struct BackOut {};
    struct BackInOut {};
    using Back = BackInOut;

    struct BounceIn {};
    struct BounceOut {};
    struct BounceInOut {};
    using Bounce = BounceInOut;

    struct CircIn {};
    struct CircOut {};
    struct CircInOut {};
    using Circ = CircInOut;

    struct CubicIn {};
    struct CubicOut {};
    struct CubicInOut {};
    using Cubic = CubicInOut;

    struct ElasticIn {};
    struct ElasticOut {};
    struct ElasticInOut {};
    using Elastic = ElasticInOut;

    struct ExpoIn {};
    struct ExpoOut {};
    struct ExpoInOut {};
    using Expo = ExpoInOut;

    struct LinearIn {};
    struct LinearOut {};
    struct LinearInOut {};
    using Linear = LinearInOut;

    struct QuadIn {};
    struct QuadOut {};
    struct QuadInOut {};
    using Quad = QuadInOut;

    struct QuartIn {};
    struct QuartOut {};
    struct QuartInOut {};
    using Quart = QuartInOut;

    struct QuintIn {};
    struct QuintOut {};
    struct QuintInOut {};
    using Quint = QuintInOut;

    struct SineIn {};
    struct SineOut {};
    struct SineInOut {};
    using Sine = SineInOut;

} // ease
} // ht

#endif // HT_TWEEN_EASING_TYPES_H
