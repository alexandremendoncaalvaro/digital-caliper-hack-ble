#include "BLE.h"

void BLE::begin()
{
	bleSerial.begin(BLE_BAUDRATE);
    Serial.println("BLE OK!");
}

void BLE::sendData(char * message) {
	bleSerial.println(message);
}

BLE ble;
