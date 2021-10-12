#include <Tween.h>

Tween::Timeline timeline;

float a = 0.f;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // tween target value a to 10 in 5000[ms]
    timeline.add(a)
        .init(0)
        .then(10, 5000);

    Serial.println("a");

    timeline.start();  // must be started to tween items in timeline
}

void loop() {
    timeline.update();  // must be called to update tween in timeline

    // show plot if timeline runs in 10sec
    if (Serial.available()) {
        bool b_changed = false;
        char c = Serial.read();

        if (c == 'u') {
            // dynamically append transition to sequence of "a"
            timeline.append(a, 10, 5000);
            b_changed = true;
        } else if (c == 'd') {
            // this is same as above (manually)
            timeline[a].then(0, 5000);
            timeline.update_duration();
            b_changed = true;
        } else if (c == 'h') {
            timeline.append(a, 2000);  // same as timline[a].hold(2000)
            b_changed = true;
        } else if (c == 'c') {
            timeline.clear();
            timeline.add(a).init(0);
        }

        if (b_changed) {
            if (!timeline.isRunning()) {
                timeline.restart();
            }
        }
    }

    // adjust serial ouput
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 50) {
        Serial.println(a);
        prev_ms = millis();
    }
}

