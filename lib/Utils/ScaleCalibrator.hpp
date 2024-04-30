#pragma once

#include <HX711.h>
#include "Config.hpp"

class ScaleCalibrator {

public:
    ScaleCalibrator(const int& doutPin = Config::scaleDoutPin,
                    const int& sckPin = Config::scaleSckPin);

    /// @brief  Logs the calibration factor of the scale
    /// @param calibrationWeight measured in grams
    void logCalibrationFactor(const int& calibrationWeight = 300);

    /// @brief  Measures the weight in grams
    /// @details Use this function to test the correctness of the scale by
    /// configuring the previously logged calibration factor
    void measureGrams();

private:
    HX711 scale;
};
