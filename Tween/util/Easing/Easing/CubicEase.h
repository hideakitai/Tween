/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution-ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_CUBICEASE_H
#define HT_TWEEN_EASING_CUBICEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class CubicEase : public EasingBase
{
public:

    virtual ~CubicEase() {}

    virtual double easeIn(double t) const
    {
        t /= t_scale;
        return v_scale * t * t * t;
    }

    virtual double easeOut(double t) const
    {
        t = t / t_scale - 1.;
        return v_scale * (t * t * t + 1.);
    }

    virtual double easeInOut(double t) const
    {
        t /= t_scale / 2.;
        if (t < 1.) return v_scale / 2. * t * t * t;
        t -= 2.;
        return v_scale / 2. * (t * t * t + 2.);
    }
};

template <>
struct Easing<CubicIn> : public CubicEase
{
    double get(const double t) const { return CubicEase::easeIn(t); }
};

template <>
struct Easing<CubicOut> : public CubicEase
{
    double get(const double t) const { return CubicEase::easeOut(t); }
};

template <>
struct Easing<CubicInOut> : public CubicEase
{
    double get(const double t) const { return CubicEase::easeInOut(t); }
};

} // ease
} // ht

#endif
