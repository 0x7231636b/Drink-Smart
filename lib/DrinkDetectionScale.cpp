#include "DrinkDetectionScale.hpp"

DrinkDetectionScale::DrinkDetectionScale(const int& calibrationFactor,
                                         const std::function<void(const long&)>& measurementDoneAction,
                                         const int& doutPin,
                                         const int& sckPin,
                                         const int& deviation) :
    measurementDoneAction(measurementDoneAction), lastMeasuredValue(0), scale(HX711()), deviation(deviation), isRunning(false) {
    scale.begin(doutPin, sckPin);
    scale.set_scale(calibrationFactor);
    measurementThread = std::thread(measureWeight);
}

void DrinkDetectionScale::tare() { scale.tare(); }

void DrinkDetectionScale::start() {
    isRunning = true;
}

void DrinkDetectionScale::stop() {
    isRunning = false;
}

void DrinkDetectionScale::measureWeight() {
    while (true) {
        scale.tare();
        while (isRunning) {
            long currentValue = scale.get_units();
            long diff = lastMeasuredValue - currentValue;

            if (diff + deviation < 0) {
                // Refill has been detected
                lastMeasuredValue = currentValue;
            } else if (diff > deviation) {
                measurementDoneAction(diff);
            }

            delay(1000);
        }
        scale.power_down();
        delay(5000);
        scale.power_up();
    }

}
