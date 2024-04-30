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
    // drinkDetectionScale.start(); // TODO: uncomment this line to start the scale

    LOG("Setup finished");
}

ScaleCalibrator scaleCalibrator;

void loop() {
    // scaleCalibrator.logCalibrationFactor(500);

    LedToolkit::blinkRed();
    LedToolkit::blinkRed(50);
    scaleCalibrator.measureGrams();
    LOG("loop finished");
}
