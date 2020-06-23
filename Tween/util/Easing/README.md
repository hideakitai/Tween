# Easing

Easing function library for Arduino.

This library is based on the [Andy Brown's Easing Function Library](https://andybrown.me.uk/2010/12/05/animation-on-the-arduino-with-easing-functions/).
For animating example of easing functions, see website like [this](https://easings.net/en).

[Tween](https://github.com/hideakitai/Tween) library is more flexible and useful tweening library based on this easing library. Please check it for more practical use.

## Usage

```C++
EasingFunc<Ease::Sine> e;
float start;

void setup()
{
    e.duration(duration); // default duration is 1.0
    e.scale(scale); // default scale is 1.0

    start = millis() / 1000.;
}

void loop()
{
    // value moves from 0.0 to scale in duration [sec]
    float now = millis() / 1000.;
    float value = e.get(now - start);

    Serial.println(value);
}
```

## APIs

```C++
// get automatically in/out/inout value based on easing types
double get(const double t);

void duration(const double t);
void scale(const double s);
double duration() const;
double scale() const;

// you can also get in/out/inout values regardless of easing type
// (not recommended)
double easeIn(double t) const;
double easeOut(double t) const;
double easeInOut(double t) const;
```

#### `Ease::Back` family only

```C++
void overshoot(const double ovs) { v_overshoot = ovs; }
double overshoot() const { return v_overshoot; }
```

#### `Ease::Elastic` family only

```C++
void period(const double p) { v_period = p; }
void amplitude(const double a) { v_amplitude = a; }
double period() const { return v_period; }
double amplitude() const { return v_amplitude; }
```

## Easing Types

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


## License

MIT
