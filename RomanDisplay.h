
#ifndef __ROMAN_DISPLAY_H__
#define __ROMAN_DISPLAY_H__

#include <FastLED.h>

#define NUM_LEDS 30
#define PIN_LED_DATA 6

class RomanDisplay
{
public:    
    RomanDisplay();
    void printNumber(uint8_t number);
    void clearDisplay();

private:
    CRGB leds[NUM_LEDS];
    uint8_t printLedIndex = 0;
    void convertToRoman(uint8_t number, char *result);
};

#endif
