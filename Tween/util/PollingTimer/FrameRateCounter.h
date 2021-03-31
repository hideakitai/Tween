#pragma once
#ifndef HT_FRAMERATECOUNTER_H
#define HT_FRAMERATECOUNTER_H

#include "IntervalCounter.h"

class FrameRateCounter : public IntervalCounter {
public:
    explicit FrameRateCounter(const double fps = 1000000.)
    : IntervalCounter(fps_to_interval(fps)) {}

    virtual ~FrameRateCounter() {}

    inline void startFps(const double fps) {
        startFpsFromFor(fps, 0., 0.);
    }
    inline void startFpsFrom(const double fps, const double from_frame) {
        startFpsFromFor(fps, from_frame, 0.);
    }
    inline void startFpsFor(const double for_frame) {
        startFpsFromFor(getFrameRate(), 0., for_frame);
    }
    inline void startFpsFor(const double fps, const double for_frame) {
        startFpsFromFor(fps, 0., for_frame);
    }
    inline void startFpsFromFor(const double fps, const double from_frame, const double for_frame) {
        IntervalCounter::startIntervalFromFor(fps_to_interval(fps), from_frame, for_frame);
    }

    inline double frame() {
        return count();
    }

    inline void setFrameRate(const double fps) {
        setInterval(fps_to_interval(fps));
    }

    double getFrameRate() const { return 1000000. / IntervalCounter::getInterval(); }

private:
    double fps_to_interval(const double fps) const {
        if (fps <= 0.001) {
            return 1. / 0.001;  // 1000[s] = 1,000,000,000[us]
        } else if (fps >= 1000000.) {
            return 1. / 1000000.;  // 0.000001[s] = 1[us]
        } else
            return 1. / fps;
    }
};

#endif  // HT_FRAMERATECOUNTER_H
