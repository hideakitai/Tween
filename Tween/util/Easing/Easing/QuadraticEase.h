/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution-ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_QUADRATICEASE_H
#define HT_TWEEN_EASING_QUADRATICEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class QuadraticEase : public EasingBase
{
public:

    virtual ~QuadraticEase() {}

    virtual double easeIn(double t) const
    {
        t /= t_scale;
        return v_scale * t * t;
    }

    virtual double easeOut(double t) const
    {
        t /= t_scale;
        return -v_scale * t * (t - 2.);
    }

    virtual double easeInOut(double t) const
    {
        t /= t_scale / 2.;
        if (t < 1.) return v_scale / 2. * t * t;
        t -= 1.;
        return -v_scale / 2. * (t * (t - 2.) - 1.);
    }
};

template <>
struct Easing<QuadIn> : public QuadraticEase
{
    double get(const double t) const { return QuadraticEase::easeIn(t); }
};

template <>
struct Easing<QuadOut> : public QuadraticEase
{
    double get(const double t) const { return QuadraticEase::easeOut(t); }
};

template <>
struct Easing<QuadInOut> : public QuadraticEase
{
    double get(const double t) const { return QuadraticEase::easeInOut(t); }
};

} // ease
} // ht

#endif
