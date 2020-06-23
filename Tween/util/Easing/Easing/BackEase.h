/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_BACKEASE_H
#define HT_TWEEN_EASING_BACKEASE_H

#include "EasingBase.h"
#include "Types.h"

namespace ht {
namespace ease {

class BackEase : public EasingBase
{
    double v_overshoot {1.70158};

public:

    virtual ~BackEase() {}

    virtual double easeIn(double t) const
    {
        t /= t_scale;
        return v_scale * t * t * ((v_overshoot + 1.) * t - v_overshoot);
    }

    virtual double easeOut(double t) const
    {
        t = t / t_scale - 1.;
        return v_scale * (t * t * ((v_overshoot + 1.) * t + v_overshoot) + 1.);
    }

    virtual double easeInOut(double t) const
    {
        double overshoot = v_overshoot * 1.525;
        t /= t_scale / 2.;
        if(t < 1.)
            return v_scale / 2. * (t * t * ((overshoot + 1.) * t - overshoot));
        t -= 2.;
        return v_scale / 2. * (t * t * ((overshoot + 1.) * t + overshoot) + 2.);
    }

    void overshoot(const double ovs) { v_overshoot = ovs; }
    double overshoot() const { return v_overshoot; }
};

template <>
struct Easing<BackIn> : public BackEase
{
    double get(const double t) const { return BackEase::easeIn(t); }
};

template <>
struct Easing<BackOut> : public BackEase
{
    double get(const double t) const { return BackEase::easeOut(t); }
};

template <>
struct Easing<BackInOut> : public BackEase
{
    double get(const double t) const { return BackEase::easeInOut(t); }
};

} // ease
} // ht

#endif // HT_TWEEN_EASING_BACKEASE_H
