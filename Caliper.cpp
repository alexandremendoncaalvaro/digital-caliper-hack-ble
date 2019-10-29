Caliper::begin()
{
    pinMode(PIN_DATA, INPUT);
    pinMode(PIN_CLOCK, INPUT);
}

Caliper::waitForClockSignal(int signal)
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
    bitArray[bitIndex] = digitalRead(DATA_PIN);

    waitForClockSignal(HIGH);
    for (bitIndex = 1; bitIndex <= 24; bitIndex++)
    {
        waitForClockSignal(LOW);
        bitArray[bitIndex] = digitalRead(DATA_PIN);
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

string Caliper::convertFloatToStringWithUnit(float value, string unitOfMeasure){
    char buff[10];
    dtostrf(result, 4, 6, buff);
    return buff + unitOfMeasure;
}

string Caliper::decode()
{
    int bitArray[25];
    int sign = 1;
    float result = 0.0;

    readBitArray(bitArray);

    auto decimalValue = convertBinaryToDecimal(bitArray);

    auto isNegativeSign = bitArray[21] == 1;

    if (isNegativeSign)
        sign = -1;

    string unitOfMeasure = " mm";

    auto isValueInInches = bitArray[24] == 1;

    if (isValueInInches)
    {
        unitOfMeasure = " in";
        result = (value * sign) / 2000.00;
    }
    else
    {
        result = (value * sign) / 100.00;
    }

    auto valueString = convertFloatToStringWithUnit(result, unitOfMeasure);

    return valueString;
}

string Caliper::getCurrentMeasurement()
{
    string currentMeasurement = "";
    auto readPulseTime = getReadPulseTime();

    auto newBitSequenceStarted = readPulseTime > READ_TIME;
    if (newBitSequenceStarted)
        currentMeasurement = decode();

    return currentMeasurement;
}

Caliper caliper;