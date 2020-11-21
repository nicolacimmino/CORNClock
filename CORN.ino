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
#include "NRF24L01RadioDriver.h"
#include "uRTCLib.h"

#define LED_PIN 7

uRTCLib rtc(0x68);
RomanDisplay display;
NRF24L01RadioDriver *radio;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    display.clearDisplay();
    display.show();

    radio = new NRF24L01RadioDriver(2);
    radio->setRXExtendedPreamble(643234);
    radio->setTXExtendedPreamble(643234);
    radio->setTXPower(3);
    radio->setRFChannel(32);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

void loop()
{
    char buffer[64];
    uint8_t dataLen = 64;
    if (radio->receive(buffer, &dataLen, 1000))
    {       
        Serial.println(buffer); 
        char *token = strtok(buffer, ",");
        if (strcmp(*token, "^T"))
        {
            token = strtok(NULL, ",");
            uint8_t h = atoi(token);
            token = strtok(NULL, ",");
            uint8_t m = atoi(token);
            token = strtok(NULL, ",");
            uint8_t s = atoi(token);

            Serial.println(h);
            Serial.println(m);
            Serial.println(s);
            rtc.set(s, m, h, 0, 0, 0, 0);          

            digitalWrite(LED_PIN, LOW);
            delay(200);
            digitalWrite(LED_PIN, HIGH);
        }

        memset(buffer, 0, 64);
    }

    rtc.refresh();
    display.clearDisplay();
    display.printNumber(rtc.hour(), 0, 15);
    display.printNumber(rtc.minute(), 15, 15);
    display.show();
}
