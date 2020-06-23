/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_CIRCULAREASE_H
#define HT_TWEEN_EASING_CIRCULAREASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class CircularEase : public EasingBase
{
public:

    virtual ~CircularEase() {}

    virtual double easeIn(double t) const
    {
        t /= t_scale;
        return -v_scale * (sqrt(1. - t * t) - 1.);
    }

    virtual double easeOut(double t) const
    {
        t = t / t_scale - 1.;
        return v_scale * sqrt(1. - t * t);
    }

    virtual double easeInOut(double t) const
    {
        t /= t_scale / 2.;
        if(t < 1.) return -v_scale / 2. * (sqrt(1. - t * t) - 1.);
        t -= 2.;
        return v_scale / 2. * (sqrt(1. - t * t) + 1.);
    }
};

template <>
struct Easing<CircIn> : public CircularEase
{
    double get(const double t) const { return CircularEase::easeIn(t); }
};

template <>
struct Easing<CircOut> : public CircularEase
{
    double get(const double t) const { return CircularEase::easeOut(t); }
};

template <>
struct Easing<CircInOut> : public CircularEase
{
    double get(const double t) const { return CircularEase::easeInOut(t); }
};

} // ease
} // ht

#endif
