/*
 * DS3234 RTC.
 */

#include "RTC.h"

#define DS3234_CS_PIN 10

////////////////////////////////////////////////////////////////////////////////
// Prepare DS3234 for operation.
//
void RTC::initialize()
{
    // We use two pins to power the RTC so we
    //  can programmatically shut it down to preserve
    //  battery. Its onboard battery will keep the time.
    pinMode(A2, OUTPUT);
    pinMode(A1, OUTPUT);
    digitalWrite(A1, HIGH); // VCC
    digitalWrite(A2, LOW);  // GND

    // Preapare SPI bus. According to DS3234 datasheed we need MSB first and Mode 1
    pinMode(DS3234_CS_PIN, OUTPUT);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE1);

    // Control register. See DS3234 datasheet.
    // We basically disable all extra features (square wave output etc) but
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

////////////////////////////////////////////////////////////////////////////////
// Reads a register containing a BCD number and converts it to a decimaal.
//
byte RTC::readBCDRegister(byte address)
{
    digitalWrite(DS3234_CS_PIN, LOW);
    SPI.transfer(address);
    byte bcdValue = SPI.transfer(0x00);
    digitalWrite(DS3234_CS_PIN, HIGH);
    return (bcdValue & 0xF) + ((bcdValue >> 4) * 10);
}

////////////////////////////////////////////////////////////////////////////////
// Writes to a register that contains BCD values the given decimal number.
//
void RTC::writeBCDRegister(byte address, byte value)
{
    // Convert the value to a two digits BCD.
    byte bcdValue = ((value / 10) << 4) + (value % 10);

    digitalWrite(DS3234_CS_PIN, LOW);
    SPI.transfer(address + 0x80);
    SPI.transfer(bcdValue);
    digitalWrite(DS3234_CS_PIN, HIGH);
}

////////////////////////////////////////////////////////////////////////////////
// Writes the given decimal number to the given register.
//
void RTC::writeRegister(byte address, byte value)
{
    digitalWrite(DS3234_CS_PIN, LOW);
    SPI.transfer(address + 0x80);
    SPI.transfer(value);
    digitalWrite(DS3234_CS_PIN, HIGH);
}
