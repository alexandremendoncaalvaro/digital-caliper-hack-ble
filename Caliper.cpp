#include "Caliper.h"

void Caliper::begin()
{
	pinMode(PIN_DATA, INPUT);
	pinMode(PIN_CLOCK, INPUT);
}

void Caliper::waitForClockSignal(int signal)
{
	while (digitalRead(PIN_CLOCK) == signal)
	{
	}
}

unsigned long Caliper::getReadPulseTime()
{
	waitForClockSignal(LOW);
	auto time_now = micros();
	waitForClockSignal(HIGH);
	return micros() - time_now;
}

void Caliper::readBitArray(int bitArray[])
{
	int bitIndex = 0;
	bitArray[bitIndex] = digitalRead(PIN_DATA);

	waitForClockSignal(HIGH);
	for (bitIndex = 1; bitIndex <= 24; bitIndex++)
	{
		waitForClockSignal(LOW);
		bitArray[bitIndex] = digitalRead(PIN_DATA);
		waitForClockSignal(HIGH);
	}
}

float Caliper::convertBinaryToDecimal(int bitArray[])
{
	float value = 0.0;
	for (int bitIndex = 1; bitIndex <= 20; bitIndex++)
	{
		value = value + (pow(2, bitIndex - 1) * bitArray[bitIndex]);
	}
	return value;
}

char * Caliper::convertFloatToStringWithUnit(float value, char* unitOfMeasure) {
	char buff[10];
	dtostrf(value, 4, 6, buff);
	char* result = strcat(buff, unitOfMeasure);
	return result;
}

char* Caliper::decode()
{
	int bitArray[25];
	int sign = 1;
	float result = 0.0;

	readBitArray(bitArray);

	auto decimalValue = convertBinaryToDecimal(bitArray);

	auto isNegativeSign = bitArray[21] == 1;

	if (isNegativeSign)
		sign = -1;

	char* unitOfMeasure = " mm";

	auto isValueInInches = bitArray[24] == 1;

	if (isValueInInches)
	{
		unitOfMeasure = " in";
		result = (decimalValue * sign) / 2000.00;
	}
	else
	{
		result = (decimalValue * sign) / 100.00;
	}

	auto valueString = convertFloatToStringWithUnit(result, unitOfMeasure);

	return valueString;
}

char* Caliper::getCurrentMeasurement()
{
	char* currentMeasurement = "";
	auto readPulseTime = getReadPulseTime();

	auto newBitSequenceStarted = readPulseTime > READ_TIME;
	if (newBitSequenceStarted)
		currentMeasurement = decode();

	return currentMeasurement;
}

Caliper caliper;
