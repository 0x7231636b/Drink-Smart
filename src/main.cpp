#include "HX711.h"
#include <Arduino.h>
#include "DrinkDetectionScale.hpp"
#include "Logger.hpp"

#include "Config.hpp"
#include "Setup.hpp"
#include <LedToolkit.hpp>
#include <RestDrinkDetectionAction.hpp>

#include <analogWrite.h>

using namespace Setup;

DrinkDetectionScale drinkDetectionScale(Config::calibrationFactor, std::make_unique<RestDrinkDetectionAction>());

void setup() {
    LedToolkit::setupLeds();
    Serial.begin(115200);
    setupClockSpeed();
    setupStackSize();

    LedToolkit::setLedConnecting();
    setupWifi();
    setupTime();

    LedToolkit::setColor(Utils::red());
    drinkDetectionScale.start();

    LOG("Setup finished");
}

void loop() {
    delay(10000);
    LOG("loop finished");
}
