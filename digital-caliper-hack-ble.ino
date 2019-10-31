#include "Common.h"
#include "BLE.h"
#include "Caliper.h"

void setup(){
    Serial.begin(BAUDRATE_SERIAL);
    Serial.println("Serial Started!");
    caliper.begin();
}

void loop(){
    auto value = caliper.getCurrentMeasurement();
    Serial.println(value);
    delay(1000);
}