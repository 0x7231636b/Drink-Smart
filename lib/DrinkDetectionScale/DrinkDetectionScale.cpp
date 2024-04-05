#include "DrinkDetectionScale.hpp"

#include "Logger.hpp"

DrinkDetectionScale::DrinkDetectionScale(const int& calibrationFactor,
                                         std::unique_ptr<DrinkDetectionAction> drinkDetectionAction,
                                         const int& doutPin,
                                         const int& sckPin,
                                         const int& deviation) :
    scale(HX711()),
    state(State::UNDEFINED),
    tareValue(0),
    lastMeasuredValue(0),
    deviation(deviation),
    isRunning(false),
    drinkDetectionAction(std::move(drinkDetectionAction)) {

    scale.begin(doutPin, sckPin);
    scale.set_scale(calibrationFactor);
}

void DrinkDetectionScale::tare() { scale.tare(); }

void DrinkDetectionScale::start() {
    measurementThread = std::thread([this] { this->measureWeight(); });
    measurementThread.detach();
    isRunning = true;
    LOG("DrinkDetectionScale::start set isRunning to true");
}

void DrinkDetectionScale::stop() {
    isRunning = false;
}

void DrinkDetectionScale::measureWeight() {
    LOG("Starting thread");

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
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    LOG("Sleeping for 1 second and power down scale");
    scale.power_down();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scale.power_up();

    LOG("Thread finished");

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

/// @brief Handle the State::DRINKING_IN_PROGRESS state
/// @details The order of the if statements is important to be handled properly, since
/// the detection of refill and cup placed back on scale interfere due to the nature of
/// calculating with negative numbers.
/// @todo Implement a refill callback to store the data for analytics
/// @todo make the order of the if statements robust (check for negative values out of deviation range)
void DrinkDetectionScale::handleDrinkingInProgressState() {
    const long currentValue = scale.get_units();
    LOG_VALUE("Current value: ", currentValue);
    LOG_VALUE("Last measured value: ", lastMeasuredValue);
    if (currentValue > deviation && currentValue + deviation < lastMeasuredValue) {
        LOG("DRINK detected");
        drinkDetectionAction->drinkDetected(lastMeasuredValue - currentValue);
        lastMeasuredValue = currentValue;
        state = State::CUP_ON_SCALE;
    } else if (lastMeasuredValue + deviation < currentValue) {
        LOG("REFILL detected")
        // TODO: Implement a refill callback to store the data for analytics
        lastMeasuredValue = currentValue;
        state = State::CUP_ON_SCALE;
    } else if (lastMeasuredValue - currentValue < deviation) {
        LOG("Cup put back on scale w/o drinking");
        state = State::CUP_ON_SCALE;
    }
}
