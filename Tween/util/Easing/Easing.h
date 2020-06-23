/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_LIBRARY_H
#define HT_TWEEN_EASING_LIBRARY_H

#include "Easing/BackEase.h"
#include "Easing/BounceEase.h"
#include "Easing/CircularEase.h"
#include "Easing/CubicEase.h"
#include "Easing/ElasticEase.h"
#include "Easing/ExponentialEase.h"
#include "Easing/LinearEase.h"
#include "Easing/QuadraticEase.h"
#include "Easing/QuarticEase.h"
#include "Easing/QuinticEase.h"
#include "Easing/SineEase.h"

namespace Ease = ht::ease;
template <typename EasingType>
using EasingFunc = Ease::Easing<EasingType>;

#endif // HT_TWEEN_EASING_LIBRARY_H
