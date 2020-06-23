/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_QUARTICEASE_H
#define HT_TWEEN_EASING_QUARTICEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class QuarticEase : public EasingBase
{
public:

    virtual ~QuarticEase() {}

    virtual double easeIn(double t) const
    {
        t /= t_scale;
        return v_scale * t * t * t * t;
    }

    virtual double easeOut(double t) const
    {
        t = t / t_scale - 1.;
        return -v_scale * (t * t * t * t - 1.);
    }

    virtual double easeInOut(double t) const
    {
        t /= t_scale / 2.;
        if(t < 1.) return v_scale / 2. * t * t * t * t;
        t -= 2.;
        return -v_scale / 2. * (t * t * t * t - 2.);
    }
};

template <>
struct Easing<QuartIn> : public QuarticEase
{
    double get(const double t) const { return QuarticEase::easeIn(t); }
};

template <>
struct Easing<QuartOut> : public QuarticEase
{
    double get(const double t) const { return QuarticEase::easeOut(t); }
};

template <>
struct Easing<QuartInOut> : public QuarticEase
{
    double get(const double t) const { return QuarticEase::easeInOut(t); }
};

} // ease
} // ht

#endif
