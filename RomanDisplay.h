//
//  RomanDisplay wraps the logic to drive a string of WS2812B addressable LEDs and show 
//  color coded roman numerals.
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

#ifndef __ROMAN_DISPLAY_H__
#define __ROMAN_DISPLAY_H__

#include <FastLED.h>

#define NUM_LEDS 30
#define PIN_LED_DATA 6
#define ROMAN_DISPLAY_BLANK CRGB(100, 120, 120)
#define ROMAN_DISPLAY_I CRGB::Blue;
#define ROMAN_DISPLAY_V CRGB::Green;
#define ROMAN_DISPLAY_X CRGB::Red;
#define ROMAN_DISPLAY_L CRGB::Yellow;

class RomanDisplay
{
public:
    RomanDisplay();
    void printNumber(byte number, byte startIndex, byte sectionLength);
    void clearDisplay();
    void show();

private:
    CRGB leds[NUM_LEDS];
    void convertToRoman(byte number, char *result);
};

#endif
