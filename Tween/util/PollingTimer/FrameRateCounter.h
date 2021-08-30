#pragma once
#ifndef HT_FRAMERATECOUNTER_H
#define HT_FRAMERATECOUNTER_H

#include "IntervalCounter.h"

class FrameRateCounter : public IntervalCounter {
public:
    explicit FrameRateCounter(const double fps = 1000000.)
    : IntervalCounter(fps_to_interval_us(fps) * 0.000001) {}

    virtual ~FrameRateCounter() {}

    void startFromFrame(const double from_frame) {
        startFromCount(from_frame);
    }
    void startForFrame(const double for_frame, const bool loop = false) {
        startForCount(for_frame, loop);
    }
    void startFromForFrame(const double from_frame, const double for_frame, const bool loop = false) {
        startFromForCount(from_frame, for_frame, loop);
    }

    void startFps(const double fps) {
        startFpsFromForFrame(fps, 0., 0., false);
    }

    void startFpsFromSec(const double fps, const double from_sec) {
        startFpsFromForSec(fps, from_sec, 0., false);
    }
    void startFpsFromMsec(const double fps, const double from_ms) {
        startFpsFromForMsec(fps, from_ms, 0., false);
    }
    void startFpsFromUsec(const double fps, const double from_us) {
        startFpsFromForUsec(fps, from_us, 0., false);
    }
    void startFpsFromFrame(const double fps, const double from_frame) {
        startFpsFromForFrame(fps, from_frame, 0., false);
    }

    void startFpsForSec(const double fps, const double for_sec, const bool loop = false) {
        startFpsFromForSec(fps, 0., for_sec, loop);
    }
    void startFpsForMsec(const double fps, const double for_ms, const bool loop = false) {
        startFpsFromForMsec(fps, 0., for_ms, loop);
    }
    void startFpsForUsec(const double fps, const double for_us, const bool loop = false) {
        startFpsFromForUsec(fps, 0., for_us, loop);
    }
    void startFpsForFrame(const double fps, const double for_frame, const bool loop = false) {
        startFpsFromForFrame(fps, 0., for_frame, loop);
    }

    void startFpsFromForSec(const double fps, const double from_sec, const double for_sec, const bool loop = false) {
        IntervalCounter::startIntervalFromForSec(fps_to_interval_us(fps) * 0.000001, from_sec, for_sec, loop);
    }
    void startFpsFromForMsec(const double fps, const double from_ms, const double for_ms, const bool loop = false) {
        IntervalCounter::startIntervalFromForMsec(fps_to_interval_us(fps) * 0.001, from_ms, for_ms, loop);
    }
    void startFpsFromForUsec(const double fps, const double from_us, const double for_us, const bool loop = false) {
        IntervalCounter::startIntervalFromForUsec(fps_to_interval_us(fps), from_us, for_us, loop);
    }
    void startFpsFromForFrame(const double fps, const double from_frame, const double for_frame, const bool loop = false) {
        IntervalCounter::startIntervalUsecFromForCount(fps_to_interval_us(fps), from_frame, for_frame, loop);
    }

    double frame() {
        return count();
    }

    void setOffsetFrame(const double frame) {
        setOffsetUsec(getIntervalUsec() * frame);
    }

    void setFrameRate(const double fps) {
        setIntervalUsec(fps_to_interval_us(fps));
    }

    double getFrameRate() const { return 1000000. / IntervalCounter::getIntervalUsec(); }

private:
    double fps_to_interval_us(const double fps) const {
        if (fps <= 0.001) {
            return 1000000000.;  // 1000[s] = 1,000,000,000[us]
        } else if (fps >= 1000000.) {
            return 1.;  // 0.000001[s] = 1[us]
        } else
            return 1000000. / fps;
    }
};

#endif  // HT_FRAMERATECOUNTER_H
