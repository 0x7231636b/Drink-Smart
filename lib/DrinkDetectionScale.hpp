#pragma once

#include <HX711.h>
#include <functional>
#include <thread>

class DrinkDetectionScale {

public:
    DrinkDetectionScale(const int& calibrationFactor,
                        const int& doutPin = 33,
                        const int& sckPin = 32,
                        const int& deviation = 25);

    void setMeasurementDoneCallback(std::function<void(const long&)>& measurementDoneAction);

    void tare();

private:
    HX711 scale;
    long lastMeasuredValue;
    int deviation;

    std::function<void(const long&)> measurementDoneAction;

    void measureWeight();

    std::thread measurementThread;
};
