/**
 * @file DataLink.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "DataLinkItem.hpp"

#define DATA_LINK_SIZE 10

class DataLink
{
private:
    
public:
    DataLinkItem items[DATA_LINK_SIZE];
    uint8_t size;

    DataLink() {}
    ~DataLink() {}

    template <typename T>
    void addLink(T &item) {
        items[size].ptr = &item;
        items[size].size = sizeof(item);
        size++;
    }
};