/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_QUINTICEASE_H
#define HT_TWEEN_EASING_QUINTICEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class QuinticEase : public EasingBase
{
public:

    virtual ~QuinticEase() {}

    virtual double easeIn(double t) const
    {
        t /= t_scale;
        return v_scale * t * t * t * t * t;
    }

    virtual double easeOut(double t) const
    {
        t = t / t_scale - 1.;
        return v_scale * (t * t * t * t * t + 1.);
    }

    virtual double easeInOut(double t) const
    {
        t /= t_scale / 2.;
        if (t < 1.) return v_scale / 2. * t * t * t * t * t;
        t -= 2.;
        return v_scale / 2. * (t * t * t * t * t + 2.);
    }
};

template <>
struct Easing<QuintIn> : public QuinticEase
{
    double get(const double t) const { return QuinticEase::easeIn(t); }
};

template <>
struct Easing<QuintOut> : public QuinticEase
{
    double get(const double t) const { return QuinticEase::easeOut(t); }
};

template <>
struct Easing<QuintInOut> : public QuinticEase
{
    double get(const double t) const { return QuinticEase::easeInOut(t); }
};

} // ease
} // ht

#endif
