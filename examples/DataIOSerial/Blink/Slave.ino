#include "Data.h"
#include <Arduino.h>
#include <DataIOSerial.hpp>
#include <SoftwareSerial.h>

Data data;
SoftwareSerial sserial(D6, D7);
DataIOSerial dataIO;

void setup()
{
    Serial.begin(74400);
    sserial.begin(9600);
    dataIO.setPort(sserial);
    dataIO.addLink(data, DATA_IN);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    dataIO.task();
    digitalWrite(LED_BUILTIN, data.statusLed);
}