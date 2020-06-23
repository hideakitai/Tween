#include <Tween.h>
#include <FastLED.h>

Tween::Timeline timeline;
CRGB c;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    timeline.add<Ease::Sine>(c, CRGB(64, 32, 128), 5000)
        .then<Ease::Expo>(CRGB(255, 255, 255), 5000)
        .wait(3000)
        .then<Ease::Bounce>(CRGB(0, 0, 0), 7000);

    Serial.println("r, g, b"); // serial plotter label

    FastLED.addLeds<NEOPIXEL, 13>(&c, 1);

    timeline.start(); // must be started to tween items in timeline
}

void loop()
{
    timeline.update(); // must be called to update tween in timeline

    if (timeline.sec() <= 20)
    {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 20)
        {
            Serial.print(c.r); Serial.print(", ");
            Serial.print(c.g); Serial.print(", ");
            Serial.print(c.b); Serial.println();

            FastLED.show();

            prev_ms = millis();
        }
    }
    else
    {
        c = CRGB::Black;
        FastLED.show();
    }
}
