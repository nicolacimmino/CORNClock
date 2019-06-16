//
//  RTC wraps the logic to drive a DS3234 RTC Chip.
//
//  Copyright (C) 2019 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "RTC.h"

#define DS3234_CS_PIN 10
#define DS3234_VCC_PIN A1
#define DS3234_GND_PIN A2

////////////////////////////////////////////////////////////////////////////////
// Prepare DS3234 for operation.
//
void RTC::initialize()
{
    // We use two pins to power the RTC so we
    //  can programmatically shut it down to preserve
    //  battery. Its onboard battery will keep the time.
    pinMode(DS3234_VCC_PIN, OUTPUT);
    pinMode(DS3234_GND_PIN, OUTPUT);
    digitalWrite(DS3234_VCC_PIN, HIGH); 
    digitalWrite(DS3234_GND_PIN, LOW); 

    // Preapare SPI bus. According to DS3234 datasheed we need MSB first and Mode 1
    pinMode(DS3234_CS_PIN, OUTPUT);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE1);

    // Control register. See DS3234 datasheet.
    // We disable all extra features (square wave output etc) but
    //  keep the oscillator running on backup battery (bit7 to zero).
    this->writeRegister(0x0E, 0x00);
}

void RTC::setTime(int v_hour, int v_minute, int v_second)
{
    this->writeBCDRegister(0x00, v_second);
    this->writeBCDRegister(0x01, v_minute);
    this->writeBCDRegister(0x02, v_hour);
}

byte RTC::getHours()
{
    return this->readBCDRegister(2);
}

byte RTC::getMinutes()
{
    return this->readBCDRegister(1);
}

byte RTC::getSeconds()
{
    return this->readBCDRegister(0);
}

byte RTC::readBCDRegister(byte address)
{
    digitalWrite(DS3234_CS_PIN, LOW);
    SPI.transfer(address);
    byte bcdValue = SPI.transfer(0x00);
    digitalWrite(DS3234_CS_PIN, HIGH);
    return (bcdValue & 0xF) + ((bcdValue >> 4) * 10);
}

void RTC::writeBCDRegister(byte address, byte value)
{
    // Convert the value to a two digits BCD.
    byte bcdValue = ((value / 10) << 4) + (value % 10);

    this->writeRegister(address, bcdValue);    
}

void RTC::writeRegister(byte address, byte value)
{
    digitalWrite(DS3234_CS_PIN, LOW);
    SPI.transfer(address + 0x80);
    SPI.transfer(value);
    digitalWrite(DS3234_CS_PIN, HIGH);
}
