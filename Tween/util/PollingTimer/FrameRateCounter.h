#pragma once
#ifndef HT_FRAMERATECOUNTER_H
#define HT_FRAMERATECOUNTER_H

#include "IntervalCounter.h"

class FrameRateCounter : public IntervalCounter
{
    double fps {40.};
    bool is_one_start {false};

public:

    explicit FrameRateCounter(const double fps)
    : IntervalCounter(1.0 / fps)
    , fps(fps)
    , is_one_start(false)
    {}

    virtual ~FrameRateCounter() {}

    inline double frame()
    {
        return is_one_start ? (count() + 1.) : count();
    }

    inline void setFrameRate(const double rate)
    {
        fps = rate;
        setInterval(1. / fps);
    }

    inline void setFirstFrameToOne(const bool b) { is_one_start = b; }

    double getFrameRate() const { return fps; }
    bool isFristFrameOne() const { return is_one_start; }

};

#endif // HT_FRAMERATECOUNTER_H
