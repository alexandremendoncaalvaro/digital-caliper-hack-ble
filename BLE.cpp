BLE::begin()
{
    bleSerial.begin(BLE_BAUDRATE);
}

BLE::sendData(char[] message){
    bleSerial.println(message);
}

BLE ble;