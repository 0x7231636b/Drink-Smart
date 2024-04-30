#pragma once

#include "Utils.hpp"

namespace LedToolkit {

void setColor(const Utils::Color& color);
void blinkRed(int pauseTimeMs = 100, int blinkCount = 30);
void blinkGreen(int pauseTimeMs = 100, int blinkCount = 30);
void blinkBlue(int pauseTimeMs = 100, int blinkCount = 30);
void blinkOrange(int pauseTimeMs = 100, int blinkCount = 30);
void setLedConnecting();
void setupLeds();
void setColor(const Utils::Color& color);

}
