#include <Tween.h>

Tween::Timeline timeline;

float a = 0.f;
float b = 0.f;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // tween target value a to 10 in 5000[ms]
    timeline.add(a)
        .init(0)
        .then(10, 5000)
        .then(5, 5000)   // and then Ease::Linear to 5 in 5000[ms]
        .wait(3000)      // and stop 1000[ms]
        .then(0, 7000);  // and then Ease::Linear to 0 in 4000[ms]

    // Ease::Sine target value b to 10 in 5000[ms]
    timeline.add(b)
        .init(0)
        .then<Ease::Sine>(10, 5000)
        .then<Ease::Elastic>(5, 5000)  // and then Ease::Elastic to 5 in 5000[ms]
        .wait(3000)                    // and stop 1000[ms]
        .then<Ease::Bounce>(0, 7000);  // and then Ease::Bounce to 0 in 4000[ms]

    Serial.println("a, b");  // serial plotter label

    timeline.start();  // must be started to tween items in timeline
}

void loop() {
    timeline.update();  // must be called to update tween in timeline

    // show plot if timeline runs in 10sec
    if (timeline.sec() <= 20) {
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
