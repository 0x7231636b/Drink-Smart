#pragma once

#include <string>

// TODO: Find a way to replace some values like the ssid and wifiPassword with some
// kind of environment variables, see https://docs.platformio.org/en/latest/scripting/actions.html
namespace Config {

const std::string backendUrl = "http://localhost:8080/";
const uint16_t backendPort = 8080;
const std::string ssid = "SSID";
const std::string wifiPassword = "PASSWORD";

const int calibrationFactor = 422;
const int scaleDoutPin = 33;
const int scaleSckPin = 32;
const int scaleDeviation = 10;
}
