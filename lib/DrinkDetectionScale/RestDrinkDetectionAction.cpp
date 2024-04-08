#include "RestDrinkDetectionAction.hpp"

RestDrinkDetectionAction::RestDrinkDetectionAction() :
    drinkDetectionConnector(std::make_unique<RestDrinkDetectionConnector>()) {}

void RestDrinkDetectionAction::drinkDetected(const long& weight) {
    drinkDetectionConnector->sendWeight(weight);
}
