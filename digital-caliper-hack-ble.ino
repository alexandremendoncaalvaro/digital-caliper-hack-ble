#include "Common.h"
#include "BLE.h"

void setup(){
    Serial.begin(BAUDRATE_SERIAL);
    ble.begin();
    caliper.begin();
}

void loop(){
    auto value = caliper.getCurrentMeasurement();
    ble.sendData(value);
    Serial.println(value);
}