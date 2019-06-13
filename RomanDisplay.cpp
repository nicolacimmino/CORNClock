
#include "RomanDisplay.h"

RomanDisplay::RomanDisplay()
{
    FastLED.addLeds<WS2812B, PIN_LED_DATA, GRB>(this->leds, NUM_LEDS);
    FastLED.setBrightness(8);
}

void RomanDisplay::convertToRoman(uint8_t number, char *result)
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

void RomanDisplay::printNumber(uint8_t number)
{
    char romanNumeralBuffer[10];
    convertToRoman(number, romanNumeralBuffer);

    for (char *bufferIterator = romanNumeralBuffer; *bufferIterator; ++bufferIterator)
    {
        {
            switch (*bufferIterator)
            {
            case 'I':
                this->leds[printLedIndex] = CRGB::Blue;
                break;
            case 'V':
                this->leds[printLedIndex] = CRGB::Green;
                break;
            case 'X':
                this->leds[printLedIndex] = CRGB::Red;
                break;
            case 'L':
                this->leds[printLedIndex] = CRGB::Yellow;
                break;
            }
            this->printLedIndex++;
        }
    }

    this->printLedIndex++;

    FastLED.show();
}

void RomanDisplay::clearDisplay()
{
    for (int ix = 0; ix < NUM_LEDS; ix++)
    {
        this->leds[ix] = CRGB(0, 0, 0);
    }
    this->printLedIndex = 0;
}
