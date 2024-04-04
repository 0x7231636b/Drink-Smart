#include "RestDrinkDetectionConnector.hpp"

#include "Config.hpp"
#include "Utils.hpp"
#include <Logger.hpp>
#include <string>
#include <iostream>
#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

RestDrinkDetectionConnector::RestDrinkDetectionConnector() :
    client() {}

String getCurrentTimestamp() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return "0"; 
    }
    long long milliseconds = mktime(&timeinfo) * 1000LL;
    return String(milliseconds);
}

void RestDrinkDetectionConnector::sendWeight(const long& weight) {
    auto weightString = Utils::to_string(weight);
    auto timeString = getCurrentTimestamp();

    std::cout<< "Sending to Backend: " << "weight: " << weightString << " time: " << timeString.c_str() << std::endl;

    auto payload = std::make_unique<std::string>("{\"userName\": \"Nicklas\","
                                                 "\"volume\": " + weightString +
                                                 ", \"timeStamp\": " + timeString.c_str() + "}");
    std::string endpoint = Config::backendUrl + "/api/drink";

    client.begin(endpoint.c_str());
    client.addHeader("Content-Type", "application/json");
    int httpCode = client.POST(payload->c_str());

    if (httpCode > 0) { 
        String response = client.getString();  
        std::cout << "Response: " << httpCode << " - " << response.c_str() << std::endl;   
    } else {
        std::cout << "Error on sending POST: " << client.errorToString(httpCode).c_str() << std::endl;
    }
}