# PollingTimer

Arduino library to manage timing and event in a flexible way with polling


## Feature

- Four timers based on the situation
  - `PollingTimer`
  - `IntervalCounter`
  - `FrameRateCounter`
  - `OneShotTimer`
- Timer events with callback / lambda
- 64bit support


## Usage

### `PollingTimer`

``` C++
#include <PollingTimer.h>
PollingTimer timer;

void setup()
{
    Serial.begin(115200);
    timer.start();
}

void loop()
{
    if (timer.isRunning())
    {
        Serial.println(timer.msec());
    }
}
```

### `IntervalCounter`

``` C++
#include <IntervalCounter.h>
IntervalCounter interval(1.0); // interval is 1.0[sec]

void setup()
{
    interval.addEvent([&]()
    {
        Serial.print("interval count = ");
        Serial.print(interval.count());
        Serial.print(", time = ");
        Serial.println(interval.ms());
    });

    interval.start();
}

void loop()
{
    interval.update(); // event occurs if interval is changed
}
```

### `FrameRateCounter`

``` C++
#include <FrameRateCounter.h>
FrameRateCounter fps(30); // set framrate to 30[Hz]

void setup()
{
    fps.addEvent([&]()
    {
        Serial.print("frame no. = ");
        Serial.print(fps.frame());
        Serial.print(", time = ");
        Serial.println(fps.msec());
    });

    fps.start();
}

void loop()
{
    fps.update(); // event occurs if fram has changed
}
```

### `OneShotTimer`

``` C++
#include <OneShotTimer.h>
OneShotTimer onshot(5); // event will be

void setup()
{
    oneshot.addEvent([&]()
    {
        Serial.print("oneshot event, time = ");
        Serial.println(millis());
    });

    oneshot.start();
}

void loop()
{
    oneshot.update(); // event occurs only once if time has elapsed
}
```


## PollingTimer States Transition

![](resources/pollingtimer_states.jpg)


## APIs

### `PollingTimer` (also available on all timer)

``` C++
void start();
void startFrom(const double from_sec);
void startFromMsec(const double from_ms);
void startFromUsec(const double from_us);
void startFor(const double for_sec);
void startForMsec(const double for_ms);
void startForUsec(const double for_us);
void startFromFor(const double from_sec, const double for_sec);
void startFromForMsec(const double from_ms, const double for_ms);
void startFromForUsec(const double from_us, const double for_us);
void startFromForUsec64(const int64_t from_us, const int64_t for_us);

void stop();
void play();
void pause();
void restart();

bool isRunning() const;
bool isPausing() const;
bool isStopping() const;

bool hasStarted() const;
bool hasFinished() const;

int64_t usec64();
double usec();
double msec();
double sec();

double getOrigin() const;
uint32_t getOverflow() const;
double getOffset() const;
double getDuration() const;
double getRemainingTime();
double getRemainingLife();

void setOffsetUsec(const int64_t us);
void setOffsetMsec(const double ms);
void setOffsetSec(const double sec);

void addOffsetUsec(const int64_t us);
void addOffsetMsec(const double ms);
void addOffsetSec(const double sec);

void setTimeUsec(const int64_t u);
void setTimeMsec(const double m) { setTimeUsec(int64_t(m * 1000.)); }
void setTimeSec(const double s) { setTimeUsec(int64_t(s * 1000000.)); }
```

### `IntervalCounter`  (also available on `FrameRateCounter` & `OneShotTimer`)

``` C++
explicit IntervalCounter (const double sec);
void startForCount(const double duration_count = 0.);
bool update();
double count();
void setInterval(const double interval_sec);
void setOffsetCount(const double offset);
void addEvent(const std::function<void(void)>& f);
bool hasEvent() const;
```

### `FrameRateCounter` only

``` C++
explicit FrameRateCounter(const double fps);
double frame();
void setFrameRate(const double rate);
void setFirstFrameToOne(const bool b);
double getFrameRate() const;
bool isFristFrameOne() const;
```

### `OneShotTimer` only

``` C++
explicit OneShotTimer(const double sec);
OneShotTimer(const double sec, const std::function<void(void)>& f);
```

## Embedded Libraries

- [ArxTypeTraits v0.2.0](https://github.com/hideakitai/ArxTypeTraits)
- [TeensyDirtySTLErrorSolution v0.1.0](https://github.com/hideakitai/TeensyDirtySTLErrorSolution)


## Used Inside of

- [Tween](https://github.com/hideakitai/Tween)
- [SceneManager](https://github.com/hideakitai/SceneManager)
- [TaskManager](https://github.com/hideakitai/TaskManager)


## License

MIT
