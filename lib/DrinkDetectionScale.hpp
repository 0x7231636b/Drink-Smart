#pragma once

#include <HX711.h>
#include <functional>
#include <thread>

class DrinkDetectionScale {

public:
    DrinkDetectionScale(const int& calibrationFactor,
                        const std::function<void(const long&)>& measurementDoneAction,
                        const int& doutPin = 33,
                        const int& sckPin = 32,
                        const int& deviation = 25);

    void tare();
    void start();
    void stop();

private:
    HX711 scale;
    long lastMeasuredValue;
    int deviation;
    boolean isRunning;

    std::function<void(const long&)> measurementDoneAction;

    void measureWeight();

    std::thread measurementThread;
};
