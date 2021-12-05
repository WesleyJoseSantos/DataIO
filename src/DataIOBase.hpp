/**
 * @file DataIOBase.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "DataLink.hpp"

class DataIOBase
{
private:
    
protected:
    DataLink dataIn;
    DataLink dataOut;
public:
    DataIOBase() {}
    ~DataIOBase() {}

    template <typename T>
    void addLink(T &it, DataLinkDirection direction){
        switch (direction)
        {
        case DataLinkDirection::DATA_IN:
            dataIn.addLink(it);
            break;
        case DataLinkDirection::DATA_OUT:
            dataOut.addLink(it);
            break;
        default:
            break;
        }
    }

    virtual void task() = 0;
};