/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_BOUNCEEASE_H
#define HT_TWEEN_EASING_BOUNCEEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class BounceEase : public EasingBase
{
public:

    virtual ~BounceEase() {}

    virtual double easeIn(double t) const
    {
        return v_scale - easeOut(t_scale - t);
    }

    virtual double easeOut(double t) const
    {
        t /= t_scale;
        if (t < (1. / 2.75))
            return v_scale * (7.5625 * t * t);
        else if (t < (2. / 2.75))
        {
            t -= 1.5 / 2.75;
            return v_scale * (7.5625 * t * t + 0.75);
        }
        else if (t < (2.5 / 2.75))
        {
            t -= 2.25 / 2.75;
            return v_scale * (7.5625 * t * t + 0.9375);
        }
        t -= 2.625 / 2.75;
        return v_scale * (7.5625 * t * t + 0.984375);
    }

    virtual double easeInOut(double t) const
    {
        if(t < t_scale / 2.)
            return easeIn(t * 2.) * 0.5;
        else
            return easeOut(t * 2. - t_scale) * 0.5 + v_scale * 0.5;
    }
};

template <>
struct Easing<BounceIn> : public BounceEase
{
    double get(const double t) const { return BounceEase::easeIn(t); }
};

template <>
struct Easing<BounceOut> : public BounceEase
{
    double get(const double t) const { return BounceEase::easeOut(t); }
};

template <>
struct Easing<BounceInOut> : public BounceEase
{
    double get(const double t) const { return BounceEase::easeInOut(t); }
};

} // ease
} // ht

#endif
