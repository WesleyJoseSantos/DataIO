/**
 * @file DataIOWebSockets.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "DataIOBase.hpp"
#include <WebSocketsServer.h>

class DataIOWebSockets : public StaticDataIOBase
{
private:
    static WebSocketsServer _server;
    bool started;

    static void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
    {
        switch (type)
        {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
        {
            IPAddress ip = _server.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            // _server.sendTXT(num, "Connected");
        }
        break;
        case WStype_TEXT:
            Serial.printf("[%u] get Text: %s\n", num, payload);

            // send message to client
            // _server.sendTXT(num, "message here");

            // send data to all connected clients
            // _server.broadcastTXT("message here");
            break;
        case WStype_BIN:
        {
            Serial.printf("[%u] get binary length: %u\n", num, length);
            hexdump(payload, length);

            int id = payload[0];

            if (id == 255)
            {
                for (int i = 0; i < dataLink.size; i++)
                {
                    dataLink.items[i].reset();
                }
                return;
            }

            size_t size = dataLink.items[id].size;

            if (size == length - 1)
            {
                dataLink.items[id].deserialize(&payload[1]);
                dataLink.items[id].isChanged();
            }
            else
            {
                Serial.printf("Payload size[%d] != dataLink size[%d]", size, dataLink.items[id].size);
            }
            break;
        }
        case WStype_ERROR:
            break;
        case WStype_FRAGMENT_TEXT_START:
            break;
        case WStype_FRAGMENT_BIN_START:
            break;
        case WStype_FRAGMENT:
            break;
        case WStype_FRAGMENT_FIN:
            break;
        case WStype_PING:
            break;
        case WStype_PONG:
            break;
        }
    }

    void dataOutTask()
    {
        for (int i = 0; i < dataLink.size; i++)
        {
            if (dataLink.items[i].isChanged())
            {
                uint8_t size = dataLink.items[i].size;
                uint8_t id = i;
                uint8_t data[size + 1];

                data[0] = id;
                dataLink.items[i].serialize(&data[1]);
                _server.broadcastBIN(data, size + 1);
            }
        }
    }

public:
    DataIOWebSockets() {}
    ~DataIOWebSockets() {}

    void begin()
    {
        _server.begin();
        _server.onEvent(webSocketEvent);
    }

    void task() override
    {
        _server.loop();
        if (started)
        {
            dataOutTask();
        }
    }
};

WebSocketsServer DataIOWebSockets::_server(81);