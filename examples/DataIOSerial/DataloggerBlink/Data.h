/**
 * @file Data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __DATA__H__
#define __DATA__H__

#include <inttypes.h>

class IpAddress
{
private:
public:
  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;

  IpAddress() {}

  IpAddress(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
  {
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
    this->byte4 = byte4;
  }
};

class MacAddress
{
private:
public:
  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;
  uint8_t byte5;
  uint8_t byte6;

  MacAddress() {}

  MacAddress(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6)
  {
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
    this->byte4 = byte4;
    this->byte5 = byte5;
    this->byte6 = byte6;
  }
};

struct DataOut
{
  uint32_t Timer;
  bool LedStatus;
  bool Bool;
  int16_t Int;
  int16_t BlinkCount;
  float Float;
  double Double;
};

struct DataIn
{
  int16_t BlinkTimer;
  bool EnableBlink;
  bool ManualCmd;
};

#endif //!__DATA__H__