#include <Tween.h>

Tween::Timeline timeline;

float a = 0.f;
float b = 0.f;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // see how timeline mode setting affects
    timeline.mode(Tween::Mode::ONCE);  // default
    // timeline.mode(Tween::Mode::REPEAT_TL);  // repeat whole timeline
    // timeline.mode(Tween::Mode::REPEAT_SQ);  // repeat each sequence
    // timeline.mode(Tween::Mode::SAVE);       // store sequences without loop

    timeline.add(a)
        .then(10, 2000)
        .then(5, 2000)
        .wait(2000)  // this is the difference between a and b
        .then(0, 2000);

    timeline.add(b)
        .then(10, 2000)
        .then(5, 2000)
        .wait(3000)  // 1000 ms longer than a
        .then(0, 2000);

    Serial.println("a, b");  // serial plotter label

    timeline.start();  // must be started to tween items in timeline
}

void loop() {
    timeline.update();  // must be called to update tween in timeline

    // show plot
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 50) {
        Serial.print(a);
        Serial.print(", ");
        Serial.print(b);
        Serial.println();
        prev_ms = millis();
    }
}