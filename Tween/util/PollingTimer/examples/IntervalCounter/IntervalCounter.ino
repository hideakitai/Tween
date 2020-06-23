#include <IntervalCounter.h>
IntervalCounter interval(1.0); // interval is 1.0[sec]

void setup()
{
    Serial.begin(115200);
    delay(5000);

    interval.start();
}

void loop()
{
    if (interval.update())
    {
        Serial.print("interval count = ");
        Serial.print(interval.count());
        Serial.print(", time = ");
        Serial.println(interval.msec());

        if (interval.count() >= 10) interval.restart();
    }
}
