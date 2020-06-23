#include <PollingTimer.h>

PollingTimer timer;

void setup()
{
    Serial.begin(115200);
    delay(5000);

    timer.start();
}

void loop()
{
    if (timer.isRunning())
    {
        Serial.print("millis() : ");
        Serial.print(millis());
        Serial.print(", timer : ");
        Serial.println(timer.msec());
    }

    delay(500);

    if (timer.msec() > 5000)
    {
        timer.setTimeSec(0); // set current time to 0sec
        Serial.println("time is set to 0sec");;
    }
}
