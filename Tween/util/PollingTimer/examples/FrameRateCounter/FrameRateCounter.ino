#include <FrameRateCounter.h>

FrameRateCounter fps(1);

void setup()
{
    Serial.begin(115200);
    delay(5000);

    fps.start();
}

void loop()
{
    if (fps.update())
    {
        Serial.print("frame no. = ");
        Serial.print(fps.frame());
        Serial.print(", time = ");
        Serial.println(fps.msec());

        if (fps.frame() >= 10) fps.restart();
    }
}
