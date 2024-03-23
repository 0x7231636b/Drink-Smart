#pragma once

#include <HX711.h>
#include <functional>
#include <thread>

/// @brief Class to detect if a drink on the scale has lost weight
/// @details The class uses a HX711 scale to measure the weight of a drink.
/// The class can detect if the drink has lost weight and calls a callback function
/// with the weight difference as argument. The callback is responsible for
/// handling the weight difference e.g. by sending it to the server or simply
/// logging it (or both).
///
/// When creating the class, we need to have no drink on the scale to calibrate
/// the scale. See the logs for when the calibration is done and a drink can
/// be placed on the scale.
class DrinkDetectionScale {

public:
    enum class State {
        UNDEFINED,
        INITIALIZED,
        CUP_ON_SCALE,
        DRINKING_IN_PROGRESS,
    };

public:
    DrinkDetectionScale(const int& calibrationFactor,
                        const std::function<void(const long&)>& measurementDoneAction,
                        const int& doutPin = 33,
                        const int& sckPin = 32,
                        const int& deviation = 10);

    void tare();
    void start();
    void stop();

private:
    HX711 scale;
    State state;
    long tareValue;
    long lastMeasuredValue;
    int deviation;
    boolean isRunning;

    std::function<void(const long&)> measurementDoneAction;
    std::thread measurementThread;

    void measureWeight();

    void handleInitializedState();
    void handleCupOnScaleState();
    void handleDrinkingInProgressState();
    void handleDifferenceDetectedState();

};
