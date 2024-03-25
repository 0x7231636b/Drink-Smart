#include "DrinkDetectionConnector.hpp"

#include "Config.hpp"
#include "Utils.hpp"
#include <Logger.hpp>
#include <string>
#include <iostream>
#include <Arduino.h>

DrinkDetectionConnector::DrinkDetectionConnector() :
    client() {}

void DrinkDetectionConnector::sendWeight(const long& weight) {
    auto weightString = Utils::to_string(weight);
    auto timeString = Utils::to_string(Utils::timeInMs());

    std::string payload = "{\"userName\": dev,"
                          "\"volume\": " + weightString + ","
                          ", \"timeStamp\": " + timeString + "}";
    std::string endpoint = Config::backendUrl + "/drinkdetection/add";

    client.begin(endpoint.c_str());
    client.addHeader("Content-Type", "application/json");
    client.POST(payload.c_str());
}
