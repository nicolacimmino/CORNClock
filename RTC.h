/*
 * DS3234 RTC.
 */

#ifndef __RTC_H__
#define __RTC_H__

#include <Arduino.h>
#include <SPI.h>

class RTC
{
public:
  void initialize();
  void setTime(int v_hour, int v_minute, int v_second);
  byte getHours();
  byte getMinutes();
  byte getSeconds();

private:
  byte readBCDRegister(byte address);
  void writeBCDRegister(byte address, byte value);
  void writeRegister(byte address, byte value);
};

#endif