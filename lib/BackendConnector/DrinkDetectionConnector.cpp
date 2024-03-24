#include "DrinkDetectionConnector.hpp"

#include <chrono>

#include "Configuration.hpp"

DrinkDetectionConnector::DrinkDetectionConnector() : client("http://localhost:8080/") {
    client.begin(Configuration::SSID, Configuration::PASSWORD);
}

DrinkDetectionConnector::sendWeight(const long& weight) {
    String weightString = String(weight);

// TODO: Create a simple JSON creator that takes a map and creates a JSON string from the key-value pairs
    String payload = "{\"userName\": " + dev +
                     ", \"volume\": " + weightString +
                     ", \"timeStamp\": " + std::chrono::system_clock::now() + "}";

    client.post("/drinkdetection/add", "application/json", payload);
}
