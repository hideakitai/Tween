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

class PollingTimer {
protected:
    static constexpr int64_t UINT32_NUMERIC_LIMIT_MAX {0x00000000FFFFFFFF};
    static constexpr uint32_t UINT32_NUMERIC_LIMIT_HALF {0x7FFFFFFF};

    bool running {false};
    bool prev_running {false};

    uint32_t prev_us32 {0};
    int64_t prev_us64 {0};
    int64_t origin {0};
    uint32_t ovf {0};
    int64_t offset {0};
    int64_t duration {0};
    bool b_loop {false};

    std::function<void(void)> cb_start;
    std::function<void(void)> cb_pause;
    std::function<void(void)> cb_stop;

public:
    virtual ~PollingTimer() {}

    virtual void start() {
        startFromForUsec64(0, 0, false);
    }

    void startFromSec(const double from_sec) {
        startFromForUsec64(from_sec * 1000000., 0, false);
    }
    void startFromMsec(const double from_ms) {
        startFromForUsec64(from_ms * 1000., 0, false);
    }
    void startFromUsec(const double from_us) {
        startFromForUsec64(from_us, 0, false);
    }

    void startForSec(const double for_sec, const bool loop = false) {
        startFromForUsec64(0, for_sec * 1000000., loop);
    }
    void startForMsec(const double for_ms, const bool loop = false) {
        startFromForUsec64(0, for_ms * 1000., loop);
    }
    void startForUsec(const double for_us, const bool loop = false) {
        startFromForUsec64(0, for_us, loop);
    }

    void startFromForSec(const double from_sec, const double for_sec, const bool loop = false) {
        startFromForUsec64(from_sec * 1000000., for_sec * 1000000., loop);
    }
    void startFromForMsec(const double from_ms, const double for_ms, const bool loop = false) {
        startFromForUsec64(from_ms * 1000., for_ms * 1000., loop);
    }
    void startFromForUsec(const double from_us, const double for_us, const bool loop = false) {
        startFromForUsec64(from_us, for_us, loop);
    }
    void startFromForUsec64(const int64_t from_us, const int64_t for_us, const bool loop = false) {
        prev_running = running;
        running = true;
        prev_us32 = MICROS();
        origin = prev_us64 = (int64_t)prev_us32;
        ovf = 0;
        offset = from_us;
        duration = for_us;
        b_loop = loop;
    }

    virtual void stop() {
        prev_running = running;
        running = false;
        prev_us32 = 0;
        origin = prev_us64 = 0;
        ovf = 0;
        // offset
        // duration
        // b_loop
    }

    virtual void play() {
        if (isPausing()) {
            prev_running = running;
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
            // No need to change
            // ovf
            // offset
            // duration
            // b_loop
        } else if (isRunning())
            ;
        else
            restart();
    }

    virtual void pause() {
        if (isRunning()) {
            microsec();
            prev_running = running;
            running = false;
            // No need to change
            // origin
            // prev_us32
            // prev_us64
            // ovf
            // offset
            // duration
            // b_loop
        }
    }

    virtual void restart() {
        stop();
        startFromForUsec64(offset, duration, b_loop);
    }

    virtual void clear() {
        prev_running = false;
        running = false;
        prev_us32 = 0;
        origin = prev_us64 = 0;
        ovf = 0;
        offset = 0;
        duration = 0;
        b_loop = false;
    }

    bool isRunning() const { return running; }
    bool isPausing() const { return (!running && (origin != 0)); }
    bool isStopping() const { return (!running && (origin == 0)); }

    bool hasStarted() const { return isRunning() && !prev_running; }
    bool hasPaused() const { return isPausing() && prev_running; }
    bool hasStopped() const { return isStopping() && prev_running; }
    void releaseEventTrigger() { prev_running = running; }

    int64_t usec64() { return microsec(); }
    double usec() { return (double)microsec(); }
    double msec() { return usec() * 0.001; }
    double sec() { return usec() * 0.000001; }

    double getOrigin() const { return (double)origin; }
    uint32_t getOverflow() const { return ovf; }

    double getOffsetUsec64() const { return offset; }
    double getOffsetUsec() const { return (double)offset; }
    double getOffsetMsec() const { return (double)offset * 0.001; }
    double getOffsetSec() const { return (double)offset * 0.000001; }

    int64_t getDurationUsec64() const { return duration; }
    double getDurationUsec() const { return (double)duration; }
    double getDurationMsec() const { return (double)duration * 0.001; }
    double getDurationSec() const { return (double)duration * 0.000001; }

    double getRemainingTime() { return (double)duration - usec(); }
    double getRemainingLife() { return (double)duration - usec() / (double)duration; }

    void setOffsetUsec64(const int64_t us) { offset = us; }
    void setOffsetUsec(const double us) { setOffsetUsec64(int64_t(us)); }
    void setOffsetMsec(const double ms) { setOffsetUsec64(int64_t(1000. * ms)); }
    void setOffsetSec(const double sec) { setOffsetUsec64(int64_t(1000000. * sec)); }

    void addOffsetUsec64(const int64_t us) { setOffsetUsec64(offset + us); }
    void addOffsetUsec(const double us) { setOffsetUsec64(int64_t(us)); }
    void addOffsetMsec(const double ms) { addOffsetUsec64(int64_t(1000. * ms)); }
    void addOffsetSec(const double sec) { addOffsetUsec64(int64_t(1000000. * sec)); }

    void setDurationUsec64(const int64_t us) { duration = us; }
    void setDurationUsec(const double us) { setDurationUsec64(int64_t(us)); }
    void setDurationMsec(const double ms) { setDurationUsec64(int64_t(1000. * ms)); }
    void setDurationSec(const double sec) { setDurationUsec64(int64_t(1000000. * sec)); }

    void setTimeUsec64(const int64_t u) {
        if (isStopping()) {
            prev_us32 = MICROS();
            prev_us64 = (int64_t)prev_us32;
            origin = prev_us64 - u;
            offset = 0;
        } else if (isPausing()) {
            int64_t diff_us = (int64_t)MICROS() - (int64_t)prev_us32;
            if (diff_us >= 0) {
                // overflow
                if ((int64_t)UINT32_NUMERIC_LIMIT_MAX - (int64_t)prev_us32 < diff_us) {
                    prev_us32 += (uint32_t)diff_us;  // overflow
                    ++ovf;
                } else {
                    prev_us32 += (uint32_t)diff_us;
                }
            }
            // overflow
            else {
                diff_us = (int64_t)MICROS() + ((int64_t)UINT32_NUMERIC_LIMIT_MAX - (int64_t)prev_us32);
                prev_us32 += (uint32_t)diff_us;  // overflow
                ++ovf;
            }
            prev_us64 += diff_us;
            origin += diff_us;
            setOffsetUsec(u - elapsed());
        } else {  // isRunning()
            setOffsetUsec(u - elapsed());
        }
    }
    void setTimeUsec(const double u) { setTimeUsec64(int64_t(u)); }
    void setTimeMsec(const double m) { setTimeUsec64(int64_t(m * 1000.)); }
    void setTimeSec(const double s) { setTimeUsec64(int64_t(s * 1000000.)); }

    void setLoop(const bool b) { b_loop = b; }
    bool isLoop() const { return b_loop; }

    bool hasOffset() const { return offset != 0; }
    bool hasDuration() const { return duration != 0; }

    void onStart(const std::function<void(void)>& cb) { cb_start = cb; }
    void onPause(const std::function<void(void)>& cb) { cb_pause = cb; }
    void onStop(const std::function<void(void)>& cb) { cb_stop = cb; }

    void removeEventOnStart() { cb_start = nullptr; }
    void removeEventOnPause() { cb_pause = nullptr; }
    void removeEventOnStop() { cb_stop = nullptr; }

    bool hasEventOnStart() const { return (bool)cb_start; }
    bool hasEventOnPause() const { return (bool)cb_pause; }
    bool hasEventOnStop() const { return (bool)cb_stop; }

protected:
    int64_t microsec() {
        if (isRunning()) {
            if (cb_start && hasStarted()) cb_start();
            prev_running = true;

            int64_t t = elapsed() + offset;
            if ((t >= duration) && (duration != 0)) {
                if (b_loop) {
                    t = 0;
                    restart();
                } else {
                    t = prev_us64 - origin + offset;
                    stop();
                }
            }
            return t;
        } else if (isPausing()) {
            if (cb_pause && hasPaused()) cb_pause();
            prev_running = false;
            return prev_us64 - origin + offset;
        } else {
            if (cb_stop && hasStopped()) cb_stop();
            prev_running = false;
            return 0;
        }
    }

    int64_t elapsed() {
        uint32_t curr_us32 = MICROS();

        if (curr_us32 < prev_us32)  // check overflow and interrupt
        {
            if (MICROS() < prev_us32)  // overflow
            {
                if (prev_us32 - MICROS() > UINT32_NUMERIC_LIMIT_HALF)
                    ++ovf;
            } else  // interrupted and changed prev_us after curr_us is captured
            {
                curr_us32 = MICROS();  // update curr_us
            }
        }
        prev_us32 = curr_us32;
        const int64_t now = (int64_t)curr_us32 | ((int64_t)ovf << 32);
        prev_us64 = now;
        return now - origin;
    }
};

#endif  // HT_POLLINGTIMER_H
