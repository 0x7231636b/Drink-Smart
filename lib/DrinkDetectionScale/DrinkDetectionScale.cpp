#include "DrinkDetectionScale.hpp"

#include "Logger.hpp"

DrinkDetectionScale::DrinkDetectionScale(const int& calibrationFactor,
                                         const std::function<void(const long&)>& measurementDoneAction,
                                         const int& doutPin,
                                         const int& sckPin,
                                         const int& deviation) :
    scale(HX711()),
    state(State::UNDEFINED),
    tareValue(0),
    lastMeasuredValue(0),
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
        tareValue = scale.get_units();

        state = State::INITIALIZED;

        lastMeasuredValue = tareValue;
        LOG_VALUE("Tare done, testing measurement: ", tareValue);
        while (isRunning) {
            switch (state) {
            case State::UNDEFINED :
                LOG("State is UNDEFINED");
                break;
            case State::INITIALIZED :
                LOG("State is INITIALIZED");
                handleInitializedState();
                break;
            case State::CUP_ON_SCALE :
                LOG("State is CUP_ON_SCALE");
                handleCupOnScaleState();
                break;
            case State::DRINKING_IN_PROGRESS :
                LOG("State is DRINKING_IN_PROGRESS");
                handleDrinkingInProgressState();
                break;
            }
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

void DrinkDetectionScale::handleInitializedState() {
    // cup set on the scale
    const long currentValue = scale.get_units();
    if (tareValue + deviation < currentValue) {
        lastMeasuredValue = currentValue;
        state = State::CUP_ON_SCALE;
    }
}

void DrinkDetectionScale::handleCupOnScaleState() {
    const long currentValue = scale.get_units();
    if (lastMeasuredValue - currentValue > deviation) {
        state = State::DRINKING_IN_PROGRESS;
    }
}

void DrinkDetectionScale::handleDrinkingInProgressState() {
    const long currentValue = scale.get_units();
    if (currentValue > deviation && currentValue + deviation < lastMeasuredValue) {
        LOG("Drink detected");
        measurementDoneAction(lastMeasuredValue - currentValue);
        lastMeasuredValue = currentValue;
        state = State::CUP_ON_SCALE;
    } else if (lastMeasuredValue - currentValue < deviation) {
        LOG("Put back on scale w/o drinking");
        // Put back on scale w/o drinking
        state = State::CUP_ON_SCALE;
    } else if (lastMeasuredValue + deviation < currentValue) {
        LOG("Refill detected")
        // TODO: Correct refill detection properly
        // TODO: Implement a refill callback to store the data for analytics
        lastMeasuredValue = currentValue;
    }
}
