//
//  A palm shaped lamp showing the current time in COlour coded Roman Numerals.
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


#include "RomanDisplay.h"
#include <DCServices.h>
#include "uRTCLib.h"

#define LED_PIN 7

uRTCLib rtc(0x68);
RomanDisplay display;
NRF24L01RadioDriver *radio;

DCServices *dcServices;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    display.clearDisplay();
    display.show();

    dcServices = new DCServices(DC_RADIO_NRF24_V2, &rtc);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

void loop()
{
    bool syncOK = dcServices->syncRTCToTimeBroadcast();
    if (syncOK)
    {
        digitalWrite(LED_PIN, LOW);
        delay(100);
        digitalWrite(LED_PIN, HIGH);
    }

    rtc.refresh();
    display.clearDisplay();
    display.printNumber(rtc.hour(), 0, 15);
    display.printNumber(rtc.minute(), 15, 15);
    display.show();
}
