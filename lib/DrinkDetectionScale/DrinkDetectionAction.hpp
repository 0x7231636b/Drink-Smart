#pragma once

class DrinkDetectionAction {

public:
    virtual ~DrinkDetectionAction() = default;

    virtual void drinkDetected(const long& weight) = 0;
};
