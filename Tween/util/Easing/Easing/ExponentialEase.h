/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution-ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_EXPONENTIALEASE_H
#define HT_TWEEN_EASING_EXPONENTIALEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class ExponentialEase : public EasingBase
{
public:

    virtual ~ExponentialEase() {}

    virtual double easeIn(double t) const
    {
        return (t == 0.) ? 0. : v_scale * pow(2., 10. * (t / t_scale - 1.));
    }

    virtual double easeOut(double t) const
    {
        return (t == t_scale) ? v_scale : v_scale * (-pow(2., -10. * t / t_scale) + 1.);
    }

    virtual double easeInOut(double t) const
    {
        if(t == 0.)       return 0;
        if(t == t_scale) return v_scale;
        t /= t_scale / 2.;
        if(t < 1.) return v_scale / 2. * pow(2., 10. * (t - 1.));
        t -= 1.;
        return v_scale / 2. * (-pow(2., -10. * t) + 2.);
    }
};

template <>
struct Easing<ExpoIn> : public ExponentialEase
{
    double get(const double t) const { return ExponentialEase::easeIn(t); }
};

template <>
struct Easing<ExpoOut> : public ExponentialEase
{
    double get(const double t) const { return ExponentialEase::easeOut(t); }
};

template <>
struct Easing<ExpoInOut> : public ExponentialEase
{
    double get(const double t) const { return ExponentialEase::easeInOut(t); }
};

} // ease
} // ht

#endif
