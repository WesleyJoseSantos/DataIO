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
    uint8_t idx;
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
        if(dataLink.items[idx].isChanged()){
            uint8_t *ptr = (uint8_t*)dataLink.items[idx].ptr;
            port->write(idx);
            for (size_t i = 0; i < dataLink.items[idx].size; i++)
            {
                port->write(*ptr);
                ptr++;
            }
        }
        idx++;
        if(idx >= dataLink.size){
            idx = 0;
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