#include "LedToolkit.hpp"

#include <Arduino.h>
#include <analogWrite.h>
#include "Config.hpp"
#include "Utils.hpp"

namespace LedToolkit {
void setColor(const Utils::Color& color) {
    analogWrite(Config::ledPinRed, color.red);
    analogWrite(Config::ledPinGreen, color.green);
    analogWrite(Config::ledPinBlue, color.blue);
}

void blink(const Utils::Color& color, int pauseTimeMs, int blinkCount) {
    for (int i = 0; i < blinkCount; i++) {
        if (i % 2 == 0) {
            setColor(color);
        } else {
            setColor(Utils::black());
        }
        delay(pauseTimeMs);
    }
}

void blinkRed(int pauseTimeMs, int blinkCount) {
    blink(Utils::red(), pauseTimeMs, blinkCount);
}

void blinkGreen(int pauseTimeMs, int blinkCount) {
    blink(Utils::green(), pauseTimeMs, blinkCount);
}

void blinkBlue(int pauseTimeMs, int blinkCount) {
    blink(Utils::blue(), pauseTimeMs, blinkCount);
}

void blinkOrange(int pauseTimeMs, int blinkCount) {
    blink(Utils::orange(), pauseTimeMs, blinkCount);
}

void setLedConnecting() {
    setColor(Utils::blue());
}

void setupLeds() {
    setColor(Utils::black());
}

}
