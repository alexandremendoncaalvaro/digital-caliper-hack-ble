#include "Caliper.h"

void Caliper::begin()
{
	pinMode(PIN_CLOCK, INPUT);
	pinMode(PIN_DATA, INPUT);
	Serial.println("Digital Caliper OK!");
}

void Caliper::waitChangeClockSignalFrom(int signal)
{
	while (digitalRead(PIN_CLOCK) == signal)
	{
	}
}

unsigned long Caliper::getStartReadPulseTime()
{
	while (digitalRead(PIN_CLOCK) == LOW)
	{
	}

	auto time_now = micros();

	while (digitalRead(PIN_CLOCK) == HIGH)
	{
	}

	unsigned long result = micros() - time_now;

	Serial.println(result);
	return result;
}

char *Caliper::convertFloatToStringWithUnit(float value, char *unitOfMeasure)
{
	char buff[10];
	dtostrf(value, 4, 6, buff);
	char *result = strcat(buff, unitOfMeasure);
	return result;
}

char *Caliper::decode()
{
	int sign = 1;
	long rawValue = 0;
	float value = 0.0;
	float conversionFactor = 1000.0;

	char *unitOfMeasure = "in";
	char *result = "";


	for (int bitIndex = 0; bitIndex < 23; bitIndex++)
	{
		while (digitalRead(PIN_CLOCK) == HIGH)
		{
		} //wait until clock returns to HIGH- the first bit is not needed

		while (digitalRead(PIN_CLOCK) == LOW)
		{
		} //wait until clock returns to LOW

		if (digitalRead(PIN_DATA) == LOW)
		{
			if (bitIndex < 20)
			{
				rawValue |= 1 << bitIndex;
			}

			if (bitIndex == 20)
			{
				sign = -1;
			}

			if (bitIndex == 22)
			{
				unitOfMeasure = "mm";
				conversionFactor = 50.00;
			}
		}
	}

	Serial.println(float(rawValue));

	value = ((float(rawValue) * sign) / conversionFactor);

	result = convertFloatToStringWithUnit(value, unitOfMeasure);

	return result;
}

// float Caliper::convertBinaryToDecimal(int bitArray[])
// {
// 	float value = 0.0;
// 	for (int bitIndex = 1; bitIndex <= 20; bitIndex++)
// 	{
// 		value = value + (pow(2, bitIndex - 1) * bitArray[bitIndex]);
// 	}
// 	return value;
// }

// char *Caliper::decode()
// {
// 	long bitArray = 0;
// 	int sign = 1;
// 	float result = 0.0;

// 	bitArray = readRawDataFromBits();

// 	auto decimalValue = convertBinaryToDecimal(bitArray);

// 	auto isNegativeSign = bitArray[21] == 1;

// 	if (isNegativeSign)
// 		sign = -1;

// 	char *unitOfMeasure = " mm";

// 	auto isValueInInches = bitArray[24] == 1;

// 	if (isValueInInches)
// 	{
// 		unitOfMeasure = " in";
// 		result = (decimalValue * sign) / 2000.00;
// 	}
// 	else
// 	{
// 		result = (decimalValue * sign) / 100.00;
// 	}

// 	auto valueString = convertFloatToStringWithUnit(result, unitOfMeasure);

// 	return valueString;
// }

char *Caliper::getCurrentMeasurement()
{
	char *currentMeasurement = "";

	while (digitalRead(PIN_CLOCK) == LOW)
	{
	}

	auto time_now = micros();
	while (digitalRead(PIN_CLOCK) == HIGH)
	{
	} 

	Serial.println(time_now);
	
	if ((micros() - time_now) > 500){
		Serial.println("Decode:");
		currentMeasurement = decode();
	}
	
	return currentMeasurement;
}

Caliper caliper;
