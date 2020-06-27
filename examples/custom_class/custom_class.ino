#include <Tween.h>

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0), y(0) {}
    Vec2(const float x, const float y) : x(x), y(y) {}

    Vec2 operator+ (const Vec2& rhs) const
    {
        return Vec2(x + rhs.x, y + rhs.y);
    }
    Vec2 operator- (const Vec2& rhs) const
    {
        return Vec2(x - rhs.x, y - rhs.y);
    }
    Vec2 operator* (const float f) const
    {
        return Vec2(x * f, y * f);
    }

    // CAUTION: just a simplified operator overloads
};


Tween::Timeline timeline;
Vec2 v;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    timeline.add(v)
        .then(Vec2(10, 8), 5000)
        .then(Vec2(5, 10), 5000)
        .wait(3000)
        .then<Ease::Bounce>(Vec2(0, 0), 7000);

    Serial.println("vx, vy"); // serial plotter label

    timeline.start(); // must be started to tween items in timeline
}

void loop()
{
    timeline.update(); // must be called to update tween in timeline

    if (timeline.sec() <= 20)
    {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 50)
        {
            Serial.print(v.x); Serial.print(", ");
            Serial.print(v.y); Serial.println();
            prev_ms = millis();
        }
    }
}
