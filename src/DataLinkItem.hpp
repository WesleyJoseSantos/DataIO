/**
 * @file DataLinkItem.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <inttypes.h>
#include <stddef.h>

class DataLinkItem
{
private:
    uint32_t checksum;
    uint32_t lastChecksum;

    void updateChecksum(){
        uint8_t *p = (uint8_t*)ptr;
        checksum = 0;
        for (size_t i = 0; i < size; i++)
        {
            checksum += *p * (i+1);
            p++;
        } 
    }

public:
    void *ptr;
    uint32_t size;
    
    DataLinkItem(){}
    ~DataLinkItem() {}

    bool isChanged(){
        lastChecksum = checksum;
        updateChecksum();
        return lastChecksum != checksum;
    }

    uint32_t getChecksum(){
        return checksum;
    }

    void reset(){
        checksum = 0;
        lastChecksum = 0;
    }

    void serialize(uint8_t *out){
        for (size_t i = 0; i < size; i++)
        {
            out[i] = *(uint8_t*)ptr;
        }
    }

    void deserialize(uint8_t *in){
        uint8_t *locPtr = (uint8_t*)ptr;
        for (size_t i = 0; i < size; i++)
        {
            *locPtr = in[i];
            locPtr++;
        }
    }
};