//Bluetooth Low Energy Communication Library
#pragma once
#include "Common.h"
#include <SoftwareSerial.h>

static class BLE
{
private:
    const uint8_t BLE_PIN_RX = 10;
    const uint8_t BLE_PIN_TX = 11;
    const unsigned long BLE_BAUDRATE = 9600;

    SoftwareSerial bleSerial = SoftwareSerial(BLE_PIN_RX, BLE_PIN_TX);
public:
    void begin();
    void sendData(char[] message);
};

extern BLE ble;