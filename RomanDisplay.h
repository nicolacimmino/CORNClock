
#ifndef __ROMAN_DISPLAY_H__
#define __ROMAN_DISPLAY_H__

#include <FastLED.h>

#define NUM_LEDS 30
#define PIN_LED_DATA 6

class RomanDisplay
{
public:    
    RomanDisplay();
    void printNumber(uint8_t number, uint8_t startIndex, uint8_t sectionLength);
    void clearDisplay();
    void show();

private:
    CRGB leds[NUM_LEDS];    
    void convertToRoman(uint8_t number, char *result);
};

#endif
