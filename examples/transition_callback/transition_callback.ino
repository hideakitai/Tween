#include <Tween.h>

Tween::Timeline timeline;

float a = 0.f;
float b = 0.f;

void setup() {
    Serial.begin(115200);
    delay(2000);

    timeline.add(a)
        .then(5, 5000, []() {
            Serial.println("a is 5 in 5000ms");
        })
        .then(0, 5000, []() {
            Serial.println("a is 0 in 5000ms");
        });

    timeline.add(b)
        .then<Ease::Sine>(10, 6000, []() {
            Serial.println("b is 10 in 6000ms");
        })
        .then<Ease::Sine>(0, 5000, []() {
            Serial.println("b is 0 in 5000ms");
        });

    Serial.println("a, b");  // serial plotter label

    timeline.start();  // must be started to tween items in timeline
}

void loop() {
    timeline.update();  // must be called to update tween in timeline

    // show plot if timeline runs in 10sec
    if (timeline.sec() <= 11) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 50) {
            Serial.print(a);
            Serial.print(", ");
            Serial.print(b);
            Serial.println();
            prev_ms = millis();
        }
    }
}

