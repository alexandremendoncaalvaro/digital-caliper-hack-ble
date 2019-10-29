//Digital Caliper Communication Library
#pragma once
#include "Common.h"

static class Caliper
{
private:
    const uint8_t PIN_DATA = 2;
    const uint8_t PIN_CLOCK = 3;
    const unsigned long READ_TIME = 500;

    void waitForClockSignal(int signal);
    unsigned long getReadPulseTime();
    void readBitArray(int bitArray[]);
    float convertBinaryToDecimal(int bitArray[]);
    string convertFloatToStringWithUnit(float value, string unitOfMeasure);
    string decode();
    
public:
    void begin();
    string getCurrentMeasurement();
};

extern Caliper caliper;
