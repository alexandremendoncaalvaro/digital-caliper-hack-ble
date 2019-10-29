#include "BLE.h"

void BLE::begin()
{
	bleSerial.begin(BLE_BAUDRATE);
}

void BLE::sendData(char * message) {
	bleSerial.println(message);
}

BLE ble;
