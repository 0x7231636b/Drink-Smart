#pragma once

#include <functional>

class DrinkDetectionScale {

public:
    DrinkDetectionScale(const int& calibrationFactor,
                        const int& doutPin = 33,
                        const int& sckPin = 32);

    void setMeasurementDoneCallback(std::function<void(const long&)>& measurementDoneAction);

    void tare();

private:
    HX711 scale;
    long lastMeasuredValue;

    std::function<void(const long&)> measurementDoneAction;
};
