#include "ScaleCalibrator.hpp"

#include <Logger.hpp>
#include <Utils.hpp>

ScaleCalibrator::ScaleCalibrator() :
    scale() {}

void ScaleCalibrator::measureGrams() {
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
        LOG_VALUE("Calibration factor: ", reading / 300);
    } else {
        LOG("HX711 not found.");
        delay(1000);
    }
}
