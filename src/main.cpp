#include "HX711.h"
#include "soc/rtc.h"
#include <Arduino.h>
#include "DrinkDetectionScale.hpp"
#include "Logger.hpp"
#include <WiFi.h>
#include "Config.hpp"
#include <RestDrinkDetectionAction.hpp>
#include <esp_pthread.h>

DrinkDetectionScale drinkDetectionScale(Config::calibrationFactor, std::make_unique<RestDrinkDetectionAction>());

void setupStackSize() {
    esp_pthread_cfg_t new_cfg = esp_pthread_get_default_config();

    new_cfg.stack_size = 10 * 1024;
    new_cfg.inherit_cfg = true;
    new_cfg.thread_name = "drink_detection_thread";
    new_cfg.pin_to_core = 1;

    esp_pthread_set_cfg(&new_cfg);
}

void setupClockSpeed() {
    rtc_cpu_freq_config_t config;
    rtc_clk_cpu_freq_get_config(&config);
    rtc_clk_cpu_freq_to_config(RTC_CPU_FREQ_80M, &config);
    rtc_clk_cpu_freq_set_config_fast(&config);
    LOG("Clock speed set to 80MHz");
}

void syncTime() {
    configTime(0, 0, "pool.ntp.org");
    Serial.println("Waiting for time sync");
    while (time(nullptr) < 24 * 3600) {
        delay(100);
        Serial.print(".");
    }
    LOG("Time synchronized with NTP server");
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
    setupStackSize();
    setupWifi();
    syncTime();

    drinkDetectionScale.start();
    LOG("Setup finished");
}

void loop() {
    delay(10000);
    LOG("loop finished");
}
