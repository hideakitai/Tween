/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution-ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_LINEAREASE_H
#define HT_TWEEN_EASING_LINEAREASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class LinearEase : public EasingBase
{
public:

    virtual ~LinearEase() {}

    virtual double easeIn(double t) const
    {
        return v_scale * t / t_scale;
    }

    virtual double easeOut(double t) const
    {
        return easeIn(t);
    }

    virtual double easeInOut(double t) const
    {
        return easeIn(t);
    }
};

template <>
struct Easing<LinearIn> : public LinearEase
{
    double get(const double t) const { return LinearEase::easeIn(t); }
};

template <>
struct Easing<LinearOut> : public LinearEase
{
    double get(const double t) const { return LinearEase::easeOut(t); }
};

template <>
struct Easing<LinearInOut> : public LinearEase
{
    double get(const double t) const { return LinearEase::easeInOut(t); }
};

} // ease
} // ht

#endif
