#pragma once
#ifndef HT_INTERVALCOUNTER_H
#define HT_INTERVALCOUNTER_H

#include "PollingTimer.h"

class IntervalCounter : public PollingTimer {
    double interval {1.};  // 1us == minimum interval
    double cnt {0.};

protected:
    std::function<void(void)> func;

public:
    explicit IntervalCounter(const double sec = 0.)
    : interval(interval_sec_to_usec(sec)), cnt(0.) {
    }

    virtual ~IntervalCounter() {}

    inline void startInterval(const double interval_sec) {
        startIntervalFromFor(interval_sec, 0., 0.);
    }
    inline void startIntervalFrom(const double interval_sec, const double from_count) {
        startIntervalFromFor(interval_sec, from_count, 0.);
    }
    inline void startIntervalFor(const double for_count) {
        startIntervalFromFor(interval, 0., for_count);
    }
    inline void startIntervalFor(const double interval_sec, const double for_count) {
        startIntervalFromFor(interval_sec, 0., for_count);
    }
    inline void startIntervalFromFor(const double interval_sec, const double from_count, const double for_count) {
        interval = interval_sec_to_usec(interval_sec);
        cnt = from_count;
        int64_t from_us = int64_t(from_count * interval);
        int64_t for_us = int64_t(for_count * interval);
        startFromForUsec64(from_us, for_us);
    }
    inline void startOnce() {
        startIntervalFor(1);
    }
    inline void startOnceAfter(const double after_sec) {
        startIntervalFor(after_sec, 1);
    }

    inline void stop() {
        PollingTimer::stop();
        cnt = 0;
    }

    inline void restart() {
        IntervalCounter::stop();
        start();
    }

    inline double count() {
        if (isPausing()) update();
        return (double)cnt;
    }

    inline double getInterval() const {
        return interval;
    }

    inline void setInterval(const double interval_sec) {
        interval = interval_sec_to_usec(interval_sec);
    }

    inline void setOffsetCount(const double offset) {
        setOffsetUsec(interval * offset);
    }

    inline void addEvent(const std::function<void(void)>& f) {
        func = f;
    }

    inline bool hasEvent() const {
        return (bool)func;
    }

    inline bool update() {
        if (isStopping()) return false;
        double prev_cnt = cnt;
        cnt = (double)usec() / interval;
        bool b = (floor(cnt) > 0.) && (floor(cnt) > floor(prev_cnt));
        if (b && func) func();
        return b;
    }

private:
    inline double interval_sec_to_usec(const double interval_sec) {
        if (interval_sec <= 0.000001)
            return 1.;
        else if (interval_sec >= 1000.)
            return 1000. * 1000000.;
        else
            return interval_sec * 1000000.;
    }
};

#endif  // HT_INTERVALCOUNTER_H
