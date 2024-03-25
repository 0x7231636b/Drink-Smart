#include "HX711.h"
#include "soc/rtc.h"
#include <Arduino.h>
#include "DrinkDetectionScale.hpp"
#include "Logger.hpp"
#include <WiFi.h>
#include "Config.hpp"

void printDetectedWeight(const long& weight) {
    LOG_VALUE("!!!! Detected weight difference: ", weight);
}

DrinkDetectionScale drinkDetectionScale(Config::calibrationFactor, printDetectedWeight);

void setupClockSpeed() {
    rtc_cpu_freq_config_t config;
    rtc_clk_cpu_freq_get_config(&config);
    rtc_clk_cpu_freq_to_config(RTC_CPU_FREQ_80M, &config);
    rtc_clk_cpu_freq_set_config_fast(&config);
    LOG("Clock speed set to 80MHz");
}

void setupWifi() {
    WiFi.begin(Config::ssid.c_str(), Config::wifiPassword.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    LOG_VALUE("Connected to: ", Config::ssid.c_str());
    LOG_VALUE("IP address: ", WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    setupClockSpeed();
    setupWifi();

    drinkDetectionScale.start();
    LOG("Setup finished");
}

void loop() {
    delay(10000);
    LOG("loop finished");
}
