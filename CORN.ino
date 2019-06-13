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

#include <FastLED.h>

#define NUM_LEDS 30

CRGB leds[NUM_LEDS];


int hours = 15;
int minutes = 02;
int seconds = 0;

void setup()
{
    FastLED.addLeds<WS2812B, 6, GRB>(leds, NUM_LEDS);
    FastLED.setCorrection(TypicalSMD5050);
    FastLED.setBrightness(8);
    clearDisplay();
}

void loop()
{
    clearDisplay();

    printNumber(hours);
    printRomanNumeral("W");
    printNumber(minutes);
    printRomanNumeral("W");
    printNumber(seconds);    
    FastLED.show();
    delay(1000);

    seconds = (seconds + 1) % 60;

    if(seconds == 0) {
        minutes = (minutes + 1) % 60;
    }

    if(seconds == 0 && minutes == 0) {
        hours = (hours + 1) % 24;
    }
}

uint8_t ledIndex = 0;

void printNumber(uint8_t number) 
{
    while (number)
    {
        printRomanNumeral(convert(number));
    }
}

void clearDisplay()
{
    for (int ix = 0; ix < NUM_LEDS; ix++)
    {
        leds[ix] = CRGB(0, 0, 0);
    }
    ledIndex = 0;    
}

void printRomanNumeral(const char *romanNumeral)
{
    while (*romanNumeral)
    {
        switch (*romanNumeral)
        {
        case 'I':
            leds[ledIndex] = CRGB::Blue;
            break;
        case 'V':
            leds[ledIndex] = CRGB::Green;
            break;
        case 'X':
            leds[ledIndex] = CRGB::Red;
            break;
        case 'L':
            leds[ledIndex] = CRGB::Yellow;
            break;
        case 'W':
            leds[ledIndex] = CRGB(50,50,50);
            break;            
        }
        ledIndex++;
        romanNumeral++;
    }    
}

const char *convert(uint8_t &numeral)
{
    if (numeral >= 50)
    {
        numeral -= 50;
        return "L";
    }

    if (numeral >= 40)
    {
        numeral -= 40;
        return "XL";
    }

    if (numeral >= 10)
    {
        numeral -= 10;
        return "X";
    }

    uint8_t units = numeral;
    numeral = 0;

    switch (units)
    {
    case 1:
        return "I";
    case 2:
        return "II";
    case 3:
        return "III";
    case 4:
        return "IV";
    case 5:
        return "V";
    case 6:
        return "VI";
    case 7:
        return "VII";
    case 8:
        return "VIII";
    case 9:
        return "IX";
    }

    return "";
}
