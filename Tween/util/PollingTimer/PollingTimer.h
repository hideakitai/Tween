#pragma once
#ifndef HT_POLLINGTIMER_H
#define HT_POLLINGTIMER_H

#ifdef ARDUINO
    #include <Arduino.h>
    #include "util/ArxTypeTraits/ArxTypeTraits.h"
    #include "util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"
    #define MICROS() micros()
#elif defined(OF_VERSION_MAJOR)
    #include "ofMain.h"
    #include <functional>
    #define MICROS() ofGetElapsedTimeMicros()
#else
    #error THIS PLATFORM IS NOT SUPPORTED
#endif

class PollingTimer
{
protected:

    static constexpr int64_t  UINT32_NUMERIC_LIMIT_MAX  {0x00000000FFFFFFFF};
    static constexpr uint32_t UINT32_NUMERIC_LIMIT_HALF {0x7FFFFFFF};

    bool running {false};
    bool prev_running {false};

    uint32_t prev_us32 {0};
    int64_t prev_us64 {0};
    int64_t origin {0};
    uint32_t ovf {0};
    int64_t offset {0};
    int64_t duration {0};

public:

    virtual ~PollingTimer() {}

    inline void start()
    {
        startFromForUsec64(0, 0);
    }
    inline void startFrom(const double from_sec)
    {
        startFromForUsec64(from_sec * 1000000., 0);
    }
    inline void startFromMsec(const double from_ms)
    {
        startFromForUsec64(from_ms * 1000., 0);
    }
    inline void startFromUsec(const double from_us)
    {
        startFromForUsec64(from_us, 0);
    }
    inline void startFor(const double for_sec)
    {
        startFromForUsec64(0, for_sec * 1000000.);
    }
    inline void startForMsec(const double for_ms)
    {
        startFromForUsec64(0, for_ms * 1000.);
    }
    inline void startForUsec(const double for_us)
    {
        startFromForUsec64(0, for_us);
    }
    inline void startFromFor(const double from_sec, const double for_sec)
    {
        startFromForUsec64(from_sec * 1000000., for_sec * 1000000.);
    }
    inline void startFromForMsec(const double from_ms, const double for_ms)
    {
        startFromForUsec64(from_ms * 1000., for_ms * 1000.);
    }
    inline void startFromForUsec(const double from_us, const double for_us)
    {
        startFromForUsec64(from_us, for_us);
    }
    inline void startFromForUsec64(const int64_t from_us, const int64_t for_us)
    {
        running = true;
        prev_running = false;
        prev_us32 = MICROS();
        origin = prev_us64 = (int64_t)prev_us32;
        ovf = 0;
        offset = from_us;
        duration = for_us;
    }

    inline void stop()
    {
        running = false;
        prev_running = false;
        prev_us32 = 0;
        origin = prev_us64 = 0;
        ovf = 0;
        offset = 0;
        duration = 0;
    }

    inline void play()
    {
        if (isPausing())
        {
            running = true;
            const uint32_t curr_us32 = MICROS();
            int64_t diff = 0;
            if (curr_us32 > prev_us32)
                diff = (int64_t)(curr_us32 - prev_us32);
            else
                diff = UINT32_NUMERIC_LIMIT_MAX - (int64_t)(prev_us32 - curr_us32);
            origin += diff;
            prev_us64 += diff;
            prev_us32 = curr_us32;
        }
        else if (isRunning())
            ;
        else
            restart();
    }

    inline void pause()
    {
        if (isRunning())
        {
            microsec();
            running = false;
        }
    }

    inline void restart()
    {
        stop();
        start();
    }

    inline bool isRunning() const { return running; }
    inline bool isPausing() const { return (!running && (origin != 0)); }
    inline bool isStopping() const { return (!running && (origin == 0)); }

    inline bool hasStarted() const { return running && !prev_running; }
    inline bool hasFinished() const { return !running && prev_running; }

    inline int64_t usec64() { return microsec(); }
    inline double usec() { return (double)microsec(); }
    inline double msec() { return usec() * 0.001; }
    inline double sec() { return usec() * 0.000001; }

    inline double getOrigin() const { return (double)origin; }
    inline uint32_t getOverflow() const { return ovf; }
    inline double getOffset() const { return offset; }
    inline double getDuration() const { return duration; }
    inline double getRemainingTime() { return (double)duration - usec(); }
    inline double getRemainingLife() { return (double)duration - usec() / (double)duration; }

    inline void setOffsetUsec(const int64_t us) { offset = us; }
    inline void setOffsetMsec(const double ms) { setOffsetUsec(int64_t(1000. * ms)); }
    inline void setOffsetSec(const double sec) { setOffsetUsec(int64_t(1000000. * sec)); }

    inline void addOffsetUsec(const int64_t us) { setOffsetUsec(offset + us); }
    inline void addOffsetMsec(const double ms) { addOffsetUsec(int64_t(1000. * ms)); }
    inline void addOffsetSec(const double sec) { addOffsetUsec(int64_t(1000000. * sec)); }

    inline void setTimeUsec(const int64_t u)
    {
        if (isStopping())
        {
            prev_us32 = MICROS();
            prev_us64 = (int64_t)prev_us32;
            origin = prev_us64 - u;
            offset = 0;
        }
        else if (isPausing())
        {
            int64_t diff_us = (int64_t)MICROS() - (int64_t)prev_us32;
            if (diff_us >= 0)
            {
                // overflow
                if ((int64_t)UINT32_NUMERIC_LIMIT_MAX - (int64_t)prev_us32 < diff_us)
                {
                    prev_us32 += (uint32_t)diff_us; // overflow
                    ++ovf;
                }
                else
                {
                    prev_us32 += (uint32_t)diff_us;
                }
            }
            // overflow
            else
            {
                diff_us = (int64_t)MICROS() + ((int64_t)UINT32_NUMERIC_LIMIT_MAX - (int64_t)prev_us32);
                prev_us32 += (uint32_t)diff_us; // overflow
                ++ovf;
            }
            prev_us64 += diff_us;
            origin += diff_us;
            setOffsetUsec(u - elapsed());
        }
        else // isRunning()
        {
            setOffsetUsec(u - elapsed());
        }
    }
    inline void setTimeMsec(const double m) { setTimeUsec(int64_t(m * 1000.)); }
    inline void setTimeSec(const double s) { setTimeUsec(int64_t(s * 1000000.)); }


protected:

    inline int64_t microsec()
    {
        if (isStopping()) return 0;
        if (isPausing())
        {
            if (hasFinished()) prev_running = false;
            return prev_us64 - origin + offset;
        }

        int64_t t = elapsed() + offset;
        if ((t >= duration) && (duration != 0))
        {
            running = false;
            return prev_us64 - origin + offset;
        }
        prev_running = isRunning();

        return t;
    }

    inline int64_t elapsed()
    {
        uint32_t curr_us32 = MICROS();

        if (curr_us32 < prev_us32) // check overflow and interrupt
        {
            if (MICROS() < prev_us32) // overflow
            {
                if (prev_us32 - MICROS() > UINT32_NUMERIC_LIMIT_HALF)
                    ++ovf;
            }
            else // interrupted and changed prev_us after curr_us is captured
            {
                curr_us32 = MICROS(); // update curr_us
            }
        }
        prev_us32 = curr_us32;
        const int64_t now = (int64_t)curr_us32 | ((int64_t)ovf << 32);
        prev_us64 = now;
        return now - origin;
    }
};

#endif // HT_POLLINGTIMER_H
