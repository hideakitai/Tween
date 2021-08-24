#include <Tween.h>

Tween::Timeline timeline;

float fs[5];

void setup() {
    Serial.begin(115200);
    delay(2000);

    // see how timeline mode setting affects
    timeline.mode(Tween::Mode::REPEAT_TL);  // repeat whole timeline
    // timeline.mode(Tween::Mode::REPEAT_SQ);  // repeat each sequence

    // Offset is added only once in the begging of the timeline
    // - REPEAT_TL: offset is always added in every loop
    // - REPEAT_SQ: offset is added only once in the beggining (not included in loop)
    for (size_t i = 0; i < 5; ++i) {
        timeline.add(fs[i])
            .init(0)
            .offset(i * 1000)
            .then(4, 1000)
            .then(0, 1000)
            .wait(3000);
    }

    Serial.println("f1, f2, f3, f4, f5");  // serial plotter label

    timeline.start();  // must be started to tween items in timeline
}

void loop() {
    timeline.update();  // must be called to update tween in timeline

    // show plot
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 50) {
        Serial.print(fs[0]);
        Serial.print(", ");
        Serial.print(fs[1]);
        Serial.print(", ");
        Serial.print(fs[2]);
        Serial.print(", ");
        Serial.print(fs[3]);
        Serial.print(", ");
        Serial.println(fs[4]);
        prev_ms = millis();
    }
}
