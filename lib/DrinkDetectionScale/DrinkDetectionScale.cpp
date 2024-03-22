#include "DrinkDetectionScale.hpp"

#include "Logger.hpp"

DrinkDetectionScale::DrinkDetectionScale(const int& calibrationFactor,
                                         const std::function<void(const long&)>& measurementDoneAction,
                                         const int& doutPin,
                                         const int& sckPin,
                                         const int& deviation) :
    scale(HX711()),
    lastMeasuredValue(0),
    isCupOnScale(true),
    deviation(deviation), 
    isRunning(false),
    measurementDoneAction(measurementDoneAction) {

    scale.begin(doutPin, sckPin);
    scale.set_scale(calibrationFactor);
    measurementThread = std::thread([this] { this->measureWeight(); });
    measurementThread.detach();
}

void DrinkDetectionScale::tare() { scale.tare(); }

void DrinkDetectionScale::start() {
    isRunning = true;
    LOG("DrinkDetectionScale::start set isRunning to true");
}

void DrinkDetectionScale::stop() {
    isRunning = false;
}

void DrinkDetectionScale::measureWeight() {
    LOG("Starting thread");
    while (true) {
        LOG("Taring scale");
        scale.tare();
        LOG_VALUE("Tare done, measurement: ", scale.get_units());
        while (isRunning) {
            LOG_VALUE("Last measured value: ", lastMeasuredValue);
            long currentValue = scale.get_units();
            LOG_VALUE("Current value: ", currentValue);
            long diff = lastMeasuredValue - currentValue;
            LOG_VALUE("Calculated Diff: ", diff);

            handleDrinkDetection(diff);


            LOG("Sleeping for 1 second\n");
            delay(1000);
        }
        LOG("Sleeping for 1 second and power down scale");
        scale.power_down();
        delay(1000);
        scale.power_up();
    }
        LOG("Thread finished, could not happen");

}

void DrinkDetectionScale::handleDrinkDetection(const long& diff) {
    
    if (diff + deviation < 0) {
        LOG("diff + deviation < 0");
        lastMeasuredValue = currentValue;
    } else if (diff > deviation) {
        LOG("diff > deviation");
        measurementDoneAction(diff);
    }
    else 
    {
        LOG("diff < deviation");
    }
};
