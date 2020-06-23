#include <IntervalCounter.h>
#include <FrameRateCounter.h>

IntervalCounter interval(1);
FrameRateCounter fps(2);

void setup()
{
    Serial.begin(115200);
    delay(5000);

    interval.addEvent([]()
    {
        Serial.print("IntervalCounter Event: curr time = ");
        Serial.println(millis());
    });

    fps.addEvent([]()
    {
        Serial.print("FrameRateCounter Event: curr time = ");
        Serial.println(millis());
    });

    interval.start();
    fps.start();
}

void loop()
{
    interval.update();
    fps.update();
}
