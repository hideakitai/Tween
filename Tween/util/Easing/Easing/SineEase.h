/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_SINEEASE_H
#define HT_TWEEN_EASING_SINEEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class SineEase : public EasingBase
{
public:

    virtual ~SineEase() {}

    virtual double easeIn(double t) const
    {
        return -v_scale * cos(t / t_scale * M_PI_2) + v_scale;
    }

    virtual double easeOut(double t) const
    {
        return v_scale * sin(t / t_scale * M_PI_2);
    }

    virtual double easeInOut(double t) const
    {
        return -v_scale / 2. * (cos(M_PI * t / t_scale) - 1.);
    }
};

template <>
struct Easing<SineIn> : public SineEase
{
    double get(const double t) const { return SineEase::easeIn(t); }
};

template <>
struct Easing<SineOut> : public SineEase
{
    double get(const double t) const { return SineEase::easeOut(t); }
};

template <>
struct Easing<SineInOut> : public SineEase
{
    double get(const double t) const { return SineEase::easeInOut(t); }
};

} // ease
} // ht

#endif
