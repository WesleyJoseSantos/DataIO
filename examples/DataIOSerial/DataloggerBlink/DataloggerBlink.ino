#include "Data.h"
#include <Arduino.h>
#include <DataIOSerial.hpp>
#include <ESP8266WiFi.h>

IpAddress ip;
MacAddress mac;
DataIn dataIn;
DataOut dataOut;
DataIOSerial dataIO;

void setup()
{
    Serial.begin(74400);
    dataIO.setPort(Serial);
    dataIO.addLink(ip, DATA_OUT);
    dataIO.addLink(mac, DATA_OUT);
    dataIO.addLink(dataOut, DATA_OUT);
    dataIO.addLink(dataIn, DATA_IN);
    pinMode(LED_BUILTIN, OUTPUT);

    ip = IpAddress(192, 168, 1, 10);
    mac = MacAddress(0x00, 0x00, 0x5e, 0x00, 0x53, 0xaf);

    dataIn.BlinkTimer = 1000;
}

void loop()
{
    // put your main code here, to run repeatedly:
    dataOut.Timer = millis();
    dataOut.Bool = !dataOut.Bool;
    dataOut.LedStatus = digitalRead(LED_BUILTIN);
    dataOut.Int += 1;
    dataOut.Float += 0.2;
    dataOut.Double += 0.4;
    dataIO.task();

    if(dataIn.EnableBlink){
        static unsigned long blinkTimer = 0;
        if (millis() > blinkTimer)
        {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            dataOut.BlinkCount++;
            blinkTimer = millis() + dataIn.BlinkTimer;
        }
    }else{
        digitalWrite(LED_BUILTIN, dataIn.ManualCmd);
    }

    if(dataIn.BlinkTimer < 100) dataIn.BlinkTimer = 100;

    delay(50);
}