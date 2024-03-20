#pragma once

#include <functional>

class DrinkDetectionScale {

public:
    DrinkDetectionScale(const int& calibrationFactor,
                        const int& doutPin = 33,
                        const int& sckPin = 32);
    virtual ~DrinkDetectionScale() = default;

    // TODO: research whether std::function is a reference or ptr by default, pass
    // this as reference or ptr if needed
    void setRequestSenderCallback(std::function<void(const long&)> callback);

    void tare();

private:
    HX711 scale;
    long lastMeasuredValue;

    std::function<void(const long&)> requestSender;
};
