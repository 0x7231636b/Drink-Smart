#include "RestDrinkDetectionConnector.hpp"

#include "Config.hpp"
#include "Utils.hpp"
#include <Logger.hpp>
#include <string>
#include <iostream>
#include <Arduino.h>

RestDrinkDetectionConnector::RestDrinkDetectionConnector() :
    client() {}

void RestDrinkDetectionConnector::sendWeight(const long& weight) {
    auto weightString = Utils::to_string(weight);
    auto timeString = Utils::to_string(Utils::timeInMs());

    LOG("\n------------------------------------------------------------");

    LOG_VALUE("Sending weight: ", weightString.c_str());
    LOG_VALUE("Sending timestamp: ", timeString.c_str());

    std::string payload = "{\"userName\": \"dev\","
                          "\"volume\": " + weightString + ","
                          "\"timeStamp\": " + timeString + "}";
    std::string endpoint = Config::backendUrl + ":" + Utils::to_string(Config::backendPort) + "/drinkdetection/add";

    LOG_VALUE("Sending payload: ", payload.c_str());
    LOG_VALUE("Sending to endpoint: ", endpoint.c_str());
    LOG("...");

    client.begin(endpoint.c_str());
    client.addHeader("Content-Type", "application/json");
    int status = client.POST(payload.c_str());
    LOG_VALUE("Weight sent with status: ", status);
    LOG("------------------------------------------------------------\n");
}
