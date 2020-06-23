/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_EASINGBASE_H
#define HT_TWEEN_EASING_EASINGBASE_H

namespace ht {
namespace ease {

class EasingBase
{
protected:

    double v_scale {1.};
    double t_scale {1.};

public:

    // easing API methods
    virtual double easeIn(double t) const = 0;
    virtual double easeOut(double t) const = 0;
    virtual double easeInOut(double t) const = 0;

    // common properties
    void duration(const double t) { t_scale = t; }
    void scale(const double s) { v_scale = s; }
    double duration() const { return t_scale; }
    double scale() const { return v_scale; }
};

template <typename>
struct Easing
{
    double get(const double t);
};

} // ease
} // ht

#endif
