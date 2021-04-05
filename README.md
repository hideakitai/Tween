# Tween

Tween library for Arduino


## Usage

```C++
#include <Tween.h>

Tween::Timeline timeline;
float target = 0.f;

void setup()
{
    timeline.add(target) // target tweens
        .then(10, 5000)  // to 10 in 5000[ms]
        .then(5, 5000)   // then to 5 in 5000[ms]
        .wait(1000)      // then stops 1000[ms]
        .then(0, 5000);  // then to 0 in 5000[ms]

    timeline.start();
}

void loop()
{
    timeline.update(); // must be called to tween target

    Serial.println(target); // target value tweens automatically
}
```

### Use Easing Function in Tween

```C++
timeline.add(f)
    .then<Ease::Sine>(10, 5000)
    .then<Ease::Elastic>(5, 5000)
    .wait(1000)
    .then<Ease::Bounce>(0, 5000);
```

### Set Timeline Mode

``` C++
timeline.mode(Tween::Mode::ONCE);   // default: erase sequence if finished
timeline.mode(Tween::Mode::REPEAT); // repeat sequence if finished
timeline.mode(Tween::Mode::SAVE);   // store sequence even if it finished
```

## Easing Types

If you haven't specify the easing type, default value is `Ease::Linear`.

- BackIn, BackOut, BackInOut
- BounceIn, BounceOut, BounceInOut
- CircIn, CircOut, CircInOut
- CubicIn, CubicOut, CubicInOut
- ElasticIn, ElasticOut, ElasticInOut
- ExpoIn, ExpoOut, ExpoInOut
- LinearIn, LinearOut, LinearInOut
- QuadIn, QuadOut, QuadInOut
- QuartIn, QuartOut, QuartInOut
- QuintIn, QuintOut, QuintInOut
- SineIn, SineOut, SineInOut

```C++
// alias
using Back = BackInOut;
using Bounce = BounceInOut;
using Circ = CircInOut;
using Cubic = CubicInOut;
using Elastic = ElasticInOut;
using Expo = ExpoInOut;
using Linear = LinearInOut;
using Quad = QuadInOut;
using Quart = QuartInOut;
using Quint = QuintInOut;
using Sine = SineInOut;
```


## Custom Class Adaptation

You can use custom classes if you have implemented following operators.

- `operator+(const T&)`
- `operator-(const T&)`
- `operator*(const double)`

If you have these operator overloads, you can use that variable completely as same as other built-in variables.
Please see `custom_class` example for details.


## Embedded Libraries

- [Easing v0.1.0](https://github.com/hideakitai/Easing)
- [PollingTimer v0.2.5](https://github.com/hideakitai/PollingTimer)
- [ArxTypeTraits v0.2.1](https://github.com/hideakitai/ArxTypeTraits)
- [ArxContainer v0.3.12](https://github.com/hideakitai/ArxContainer)
- [ArxSmartPtr v0.2.1](https://github.com/hideakitai/ArxSmartPtr)
- [TeensyDirtySTLErrorSolution v0.1.0](https://github.com/hideakitai/TeensyDirtySTLErrorSolution)


## License

MIT
