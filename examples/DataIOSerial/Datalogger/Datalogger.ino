#include "Data.h"
#include <Arduino.h>
#include <DataIOSerial.hpp>
#include <ESP8266WiFi.h>

Data data;
DataIOSerial dataIO;

void setup()
{
    Serial.begin(74400);
    dataIO.setPort(Serial);
    dataIO.addLink(data, DATA_OUT);
    pinMode(LED_BUILTIN, OUTPUT);

    data.Ip = IpAddress(192, 168, 0, 10);
    data.Mac = MacAddress(0x00, 0x00, 0x5e, 0x00, 0x53, 0xaf);
}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    data.Timer = millis();
    data.LedStatus = digitalRead(LED_BUILTIN);
    data.Bool = !data.Bool;
    data.Int += 1;
    data.Float += 0.2;
    data.Double += 0.4;
    dataIO.task();
    delay(1000);
}