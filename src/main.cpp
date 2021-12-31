#include "Data.h"
#include <Arduino.h>
#include <DataIOWebSockets.hpp>
#include <ESP8266WiFi.h>

#define SSID "DataIO WS Server"
#define PASS "dataiowspass" 

DataIp dataIp;
DataMac dataMac;
DataIn dataIn;
DataOut dataOut;
DataIOWebSockets dataIO;

void setup()
{
    Serial.begin(74400);
    WiFi.softAP(SSID, PASS);

    while (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Waiting for connection...");
        delay(1000);
    }

    dataIO.begin();
    dataIO.addLink(dataIp);
    dataIO.addLink(dataMac);
    dataIO.addLink(dataOut);
    dataIO.addLink(dataIn);

    pinMode(LED_BUILTIN, OUTPUT);

    IPAddress ip = WiFi.localIP();
    uint8_t mac[6];
    WiFi.macAddress(mac);

    dataIp = DataIp(ip[0], ip[1], ip[2], ip[3]);
    dataMac = DataMac(mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

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
            if(digitalRead(LED_BUILTIN)) dataOut.BlinkCount++;
            blinkTimer = millis() + dataIn.BlinkTimer;
        }
    }else{
        digitalWrite(LED_BUILTIN, dataIn.ManualCmd);
    }

    if(dataIn.BlinkTimer < 100) dataIn.BlinkTimer = 100;
    
    delay(500);
}