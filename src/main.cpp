#include "HX711.h"
#include "soc/rtc.h"
#include <Arduino.h>
#include "../lib/DrinkDetectionScale/DrinkDetectionScale.hpp"
#include "../lib/Logger/Logger.hpp"

void logCalibrationFactor();
long measureGrams();

// TODO: Edit calibrationFactor to the value you got from the
// logCalibrationFactor function
const int calibrationFactor = 422;

const int scaleDoutPin = 33;
const int scaleSckPin = 32;

HX711 scale;

void printDetectedWeight(const long& weight) {
    LOG_VALUE("!!!! Detected weight difference: ", weight);
}

DrinkDetectionScale drinkDetectionScale(calibrationFactor, printDetectedWeight);

void setupClockSpeed() {
    rtc_cpu_freq_config_t config;
    rtc_clk_cpu_freq_get_config(&config);
    rtc_clk_cpu_freq_to_config(RTC_CPU_FREQ_80M, &config);
    rtc_clk_cpu_freq_set_config_fast(&config);
    LOG("Clock speed set to 80MHz");
}

void setup() {
    Serial.begin(115200);
    setupClockSpeed();

    drinkDetectionScale.start();
    LOG("Setup finished");
}

void loop() {



    // logCalibrationFactor();
    // measureGrams();

    
    delay(1000);

    LOG("loop finished");
}

long measureGrams() {
    LOG_VALUE("Single reading: ", scale.get_units());
    LOG_VALUE("10 readings: ", scale.get_units(10));
    return 0;
}

void logCalibrationFactor() {
    if (scale.is_ready()) {
        scale.set_scale();
        LOG("Tare... remove any weights from the scale.");
        delay(5000);
        scale.tare();
        LOG("Tare done...");
        LOG("Place a known weight on the scale...");
        delay(5000);
        long reading = scale.get_units(10);
        LOG_VALUE("Result: ", reading);
        LOG(reading);
        LOG_VALUE("Calibration factor: ", reading / 300);
    } else {
        LOG("HX711 not found.");
        delay(1000);
    }
}
