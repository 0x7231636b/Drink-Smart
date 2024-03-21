#include "DrinkDetectionScale.hpp"

DrinkDetectionScale::DrinkDetectionScale(const int& calibrationFactor,
                                         const int& doutPin,
                                         const int& sckPin,
                                         const int& deviation) :
    lastMeasuredValue(0), scale(HX711()), deviation(deviation) {
    scale.begin(doutPin, sckPin);
    scale.set_scale(calibrationFactor);
    measurementThread = std::thread(measureWeight);
}

void DrinkDetectionScale::setMeasurementDoneCallback(std::function<void(const long&)>& callback) {
    this->measurementDoneAction = measurementDoneAction;
}

void DrinkDetectionScale::tare() { scale.tare(); }

void DrinkDetectionScale::measureWeight() {
    while (true) {
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
}
