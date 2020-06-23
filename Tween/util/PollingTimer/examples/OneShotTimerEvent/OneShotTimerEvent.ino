#include <OneShotTimer.h>

OneShotTimer oneshot(5);

void setup()
{
    Serial.begin(115200);
    delay(5000);

    oneshot.addEvent([]()
    {
        Serial.print("OneShot Event: curr time = ");
        Serial.println(millis());
    });

    Serial.print("OneShot Start: curr time = ");
    Serial.println(millis());
    oneshot.start();
}

void loop()
{
    oneshot.update();
}
