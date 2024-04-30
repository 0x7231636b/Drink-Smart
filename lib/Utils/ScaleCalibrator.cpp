#include "ScaleCalibrator.hpp"

#include <Logger.hpp>
#include <Utils.hpp>
#include <LedToolkit.hpp>

#include <analogWrite.h>

ScaleCalibrator::ScaleCalibrator(const int& doutPin,
                                 const int& sckPin) :
    scale(HX711()) {
    scale.begin(doutPin, sckPin);
}

void ScaleCalibrator::measureGrams() {
    LedToolkit::setColor(Utils::red());
    scale.set_scale(Config::calibrationFactor);
    scale.tare();
    LOG("Tare done, place a weight on the scale... Waiting for a couple of seconds");
    LedToolkit::blinkOrange();
    LedToolkit::setColor(Utils::red());
    LOG_VALUE("Single reading: ", scale.get_units());
    LOG_VALUE("10 readings: ", scale.get_units(10));
}

void ScaleCalibrator::logCalibrationFactor(const int& calibrationWeight) {
    if (scale.is_ready()) {
        scale.set_scale();
        LOG("Tare... remove any weights from the scale.");
        delay(5000);
        scale.tare();
        LOG("Tare done...");
        LOG(std::string("Place a known weight of " + Utils::to_string(calibrationWeight) + "g on the scale...").c_str());
        delay(5000);
        long reading = scale.get_units(10);
        LOG_VALUE("Result: ", reading);
        LOG(reading);
        LOG_VALUE("Calibration factor: ", reading / calibrationWeight);
    } else {
        LOG("HX711 not found.");
        delay(1000);
    }
}
