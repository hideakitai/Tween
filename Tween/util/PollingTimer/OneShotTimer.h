#pragma once
#ifndef HT_ONESHOTTIMER_H
#define HT_ONESHOTTIMER_H

#include "IntervalCounter.h"
#include "util/ArxTypeTraits/ArxTypeTraits.h"

class OneShotTimer : public IntervalCounter {
public:
    virtual ~OneShotTimer() {}

    explicit OneShotTimer(const double sec)
    : IntervalCounter(sec) {}

    OneShotTimer(const double sec, const std::function<void(void)>& f)
    : IntervalCounter(sec) {
        IntervalCounter::onUpdate(f);
    }

    void start() {
        IntervalCounter::startOnce();
    }
};

#endif  // HT_ONESHOTTIMER_H
