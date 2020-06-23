/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution-ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#pragma once
#ifndef HT_TWEEN_EASING_ELASTICEASE_H
#define HT_TWEEN_EASING_ELASTICEASE_H

#include "EasingBase.h"

namespace ht {
namespace ease {

class ElasticEase : public EasingBase
{
    double v_period {0};
    double v_amplitude {0};

public:

    virtual ~ElasticEase() {}

    virtual double easeIn(double t) const
    {
        if (t == 0) return 0;
        t /= t_scale;
        if (t == 1) return v_scale;

        double p, a, s;

        if (v_period == 0.) p = t_scale * 0.3;
        else               p = v_period;

        a = v_amplitude;
        if (a == 0. || a < fabs(v_scale))
        {
            a = v_scale;
            s = p / 4.;
        }
        else
            s = p / (2. * M_PI) * asin(v_scale / a);

        t -= 1.;
        return -(a * pow(2., 10. * t) * sin((t * t_scale - s) * (2. * M_PI) / p));
    }

    virtual double easeOut(double t) const
    {
        if (t == 0.) return 0;
        t /= t_scale;
        if (t == 1.) return v_scale;

        double p, a, s;

        if (v_period == 0.) p = t_scale * 0.3;
        else               p = v_period;

        a = v_amplitude;
        if (a == 0 || a < fabs(v_scale))
        {
            a = v_scale;
            s = p / 4.;
        }
        else
            s = p / (2. * M_PI) * asin(v_scale / a);

        return a * pow(2., -10. * t) * sin((t * t_scale - s) * (2. * M_PI) / p) + v_scale;
    }

    virtual double easeInOut(double t) const
    {
        if (t == 0.) return 0;
        t /= t_scale / 2.;
        if (t == 2.) return v_scale;

        double p, a, s;

        if (v_period == 0.) p = t_scale * (0.3 * 1.5);
        else               p = v_period;

        a = v_amplitude;
        if (a == 0 || a < fabs(v_scale))
        {
            a = v_scale;
            s = p / 4.;
        }
        else
            s = p / (2. * M_PI) * asin(v_scale / a);

        if (t < 1.)
        {
            t -= 1.;
            return -0.5 * (a * pow(2., 10. * t) * sin((t * t_scale - s) * (2. * M_PI) / p));
        }

        t -= 1.;
        return a * pow(2., -10. * t) * sin((t * t_scale - s) * (2. * M_PI) / p) * 0.5 + v_scale;
    }

    void period(const double p) { v_period = p; }
    void amplitude(const double a) { v_amplitude = a; }
    double period() const { return v_period; }
    double amplitude() const { return v_amplitude; }
};

template <>
struct Easing<ElasticIn> : public ElasticEase
{
    double get(const double t) const { return ElasticEase::easeIn(t); }
};

template <>
struct Easing<ElasticOut> : public ElasticEase
{
    double get(const double t) const { return ElasticEase::easeOut(t); }
};

template <>
struct Easing<ElasticInOut> : public ElasticEase
{
    double get(const double t) const { return ElasticEase::easeInOut(t); }
};

} // ease
} // ht

#endif
