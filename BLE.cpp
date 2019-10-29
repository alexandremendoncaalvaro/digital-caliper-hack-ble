#include "BLE.h"

void BLE::begin()
{
    bleSerial.begin(BLE_BAUDRATE);
}

void BLE::sendData(string message){
    bleSerial.println(message);
}

BLE ble;
