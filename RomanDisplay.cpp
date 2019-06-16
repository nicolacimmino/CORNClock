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

#include "RomanDisplay.h"

RomanDisplay::RomanDisplay()
{
    FastLED.addLeds<WS2812B, PIN_LED_DATA, GRB>(this->leds, NUM_LEDS);
    FastLED.setBrightness(255);
}

void RomanDisplay::setBrightness(byte brightness)
{    
    FastLED.setBrightness(brightness);
}

void RomanDisplay::convertToRoman(byte number, char *result)
{        
    struct
    {
        unsigned int value;
        const char *symbols;
    } romanDigits[] = {
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}};

    strcpy(result, "");
    while (number)
    {
        for (int ix = 0; ix < sizeof(romanDigits) / sizeof(*romanDigits); ix++)
        {
            if (number >= romanDigits[ix].value)
            {
                number -= romanDigits[ix].value;
                strcat(result, romanDigits[ix].symbols);
                break;
            }
        }
    }
}

void RomanDisplay::clearDisplay()
{
    for (int ix = 0; ix < NUM_LEDS; ix++)
    {
        this->leds[ix] = ROMAN_DISPLAY_BLANK;
    }    
}

void RomanDisplay::show()
{
    FastLED.show();
}

void RomanDisplay::printNumber(byte number, byte startIndex, byte sectionLength)
{
    char romanNumeralBuffer[10];
    convertToRoman(number, romanNumeralBuffer);

    startIndex += ((sectionLength - 2 * strlen(romanNumeralBuffer)) >> 1);

    CRGB colour = CRGB::White;

    for (char *bufferIterator = romanNumeralBuffer; *bufferIterator; ++bufferIterator)
    {
        {
            switch (*bufferIterator)
            {
            case 'I':
                colour = ROMAN_DISPLAY_I;
                break;
            case 'V':
                colour = ROMAN_DISPLAY_V;
                break;
            case 'X':
                colour = ROMAN_DISPLAY_X;
                break;
            case 'L':
                colour = ROMAN_DISPLAY_L;
                break;
            }

            // Due to mechanical limiations in the proto it was more handy to
            // have leds indexed counterclockwise, however, it's far more logical
            // to read the clock clocwise. We fix it here because software is 
            // cheaper than disassembling and rewiring.
            this->leds[NUM_LEDS - startIndex] = colour;            
            startIndex+=2;            
        }
    }    
}
