#pragma once

#include "DrinkDetectionAction.hpp"
#include "RestDrinkDetectionConnector.hpp"

class RestDrinkDetectionAction : public DrinkDetectionAction {

public:
    RestDrinkDetectionAction();

    void drinkDetected(const long& weight) override;

private:
    std::unique_ptr<DrinkDetectionConnector> drinkDetectionConnector;
};
