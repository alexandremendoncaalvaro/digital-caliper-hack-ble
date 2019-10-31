//Digital Caliper Communication Library
#pragma once
#include "Common.h"

class Caliper
{
private:
	const uint8_t PIN_CLOCK = 2;
	const uint8_t PIN_DATA = 3;
	const unsigned long READ_TIME = 500;

	void waitChangeClockSignalFrom(int signal);
	unsigned long getStartReadPulseTime();
	// long readRawDataFromBits();
	// float convertBinaryToDecimal(int bitArray[]);
	char* convertFloatToStringWithUnit(float value, char* unitOfMeasure);
	char* decode();

public:
	void begin();
	char* getCurrentMeasurement();
};

extern Caliper caliper;