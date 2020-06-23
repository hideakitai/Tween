#pragma once
#ifndef HT_INTERVALCOUNTER_H
#define HT_INTERVALCOUNTER_H

#include "PollingTimer.h"

class IntervalCounter : public PollingTimer
{
    double interval {0.};
    double cnt {0.};

protected:

    std::function<void(void)> func;

public:

    explicit IntervalCounter (const double sec)
    : interval(sec * 1000000.)
    , cnt(0.)
    {}

    virtual ~IntervalCounter() {}

    inline void startForCount(const double duration_count = 0.)
    {
        PollingTimer::startForUsec((int64_t)(duration_count * interval));
        cnt = 0;
    }

    inline void stop()
    {
        PollingTimer::stop();
        cnt = 0;
    }

    inline void restart()
    {
        IntervalCounter::stop();
        start();
    }

    inline double count()
    {
        if (isPausing()) update();
        return (double)cnt;
    }

    inline void setInterval(const double interval_sec)
    {
        interval = interval_sec * 1000000.;
    }

    inline void setOffsetCount(const double offset)
    {
        setOffsetUsec(interval * offset);
    }

    inline void addEvent(const std::function<void(void)>& f)
    {
        func = f;
    }

    inline bool hasEvent() const
    {
        return (bool)func;
    }

    inline bool update()
    {
        if (isStopping()) return false;
        double prev_cnt = cnt;
        cnt = (double)usec() / interval;
        bool b = (floor(cnt) > 0.) && (floor(cnt) > floor(prev_cnt));
        if (b && func) func();
        return b;
    }

};

#endif // HT_INTERVALCOUNTER_H
