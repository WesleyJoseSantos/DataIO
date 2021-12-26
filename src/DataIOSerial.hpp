/**
 * @file DataIOSerial.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "DataIOBase.hpp"
#include "Stream.h"

class DataIOSerial  :public DataIOBase
{
private:
    Stream *port;
    bool started;

    void dataInTask(){
        if(port->available()){
            int id = port->read();

            if(id == 255){
                for (int i = 0; i < dataLink.size; i++)
                {
                    dataLink.items[i].reset();
                }
                return;
            }

            int size = dataLink.items[id].size;
            uint8_t *ptr = (uint8_t*)dataLink.items[id].ptr;
            port->readBytes(ptr, size);      
            dataLink.items[id].isChanged();      
        }
    }

    void dataOutTask(){
        for (int i = 0; i < dataLink.size; i++)
        {
            if(dataLink.items[i].isChanged()){
                uint8_t *ptr = (uint8_t*)dataLink.items[i].ptr;
                port->write(i);
                for (size_t j = 0; j < dataLink.items[i].size; j++)
                {
                    port->write(*ptr);
                    ptr++;
                }
            }
        }
    }

public:
    DataIOSerial() {}
    ~DataIOSerial() {}

    void setPort(Stream &port){
        this->port = &port;
    }

    void task(){
        if(started){
            dataInTask();
            dataOutTask();
        }else{
            if(port->available()){
                int read = port->read();
                if(read == 255){
                    started = true;
                }
            }
        }
    }
};