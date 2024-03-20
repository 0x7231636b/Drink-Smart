#include "DrinkDetectionScale.hpp"

#include <HX711.h>

DrinkDetectionScale::DrinkDetectionScale(const int& calibrationFactor,
                                         const int& doutPin,
                                         const int& sckPin) :
    lastMeasuredValue(0), scale(HX711()) {
    scale.begin(doutPin, sckPin);
    scale.set_scale(calibrationFactor);

    // TODO: Implement a std::thread for the scale to measure the weight all the
    // time Think about a delay that doesn't push the cpu to the limit
    // Thread function within this implementation started by the constructor
}

void DrinkDetectionScale::setRequestSenderCallback(std::function<void(const long&)> callback) {
    requestSender = callback;
}

void DrinkDetectionScale::tare() { scale.tare(); }
