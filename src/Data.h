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
#include <WString.h>

class IpAddress
{
private:
public:
  uint8_t B1;
  uint8_t B2;
  uint8_t B3;
  uint8_t B4;

  IpAddress() {}

  IpAddress(uint8_t B1, uint8_t B2, uint8_t B3, uint8_t B4)
  {
    this->B1 = B1;
    this->B2 = B2;
    this->B3 = B3;
    this->B4 = B4;
  }
};

class MacAddress
{
private:
public:
  uint8_t B1;
  uint8_t B2;
  uint8_t B3;
  uint8_t B4;
  uint8_t B5;
  uint8_t B6;

  MacAddress() {}

  MacAddress(uint8_t B1, uint8_t B2, uint8_t B3, uint8_t B4, uint8_t B5, uint8_t B6)
  {
    this->B1 = B1;
    this->B2 = B2;
    this->B3 = B3;
    this->B4 = B4;
    this->B5 = B5;
    this->B6 = B6;
  }
};

struct DataOut
{
  unsigned long Timer;
  bool LedStatus;
  bool Bool;
  int Int;
  int BlinkCount;
  float Float;
  double Double;
};

struct DataIn
{
  int BlinkTimer;
  bool EnableBlink;
  bool ManualCmd;
};

#endif //!__DATA__H__