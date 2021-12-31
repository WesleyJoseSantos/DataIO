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
    DataLink dataLink;
public:
    DataIOBase() {}
    ~DataIOBase() {}

    template <typename T>
    void addLink(T &it){
        dataLink.addLink(it);
    }

    virtual void task() = 0;
};

class StaticDataIOBase
{
protected:
    static DataLink dataLink;
public:
    StaticDataIOBase() {}
    ~StaticDataIOBase() {}

    template <typename T>
    void addLink(T &it){
        dataLink.addLink(it);
    }

    virtual void task() = 0;
};

DataLink StaticDataIOBase::dataLink;