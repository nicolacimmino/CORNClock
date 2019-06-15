
#include "RomanDisplay.h"

RomanDisplay::RomanDisplay()
{
    FastLED.addLeds<WS2812B, PIN_LED_DATA, GRB>(this->leds, NUM_LEDS);
    FastLED.setBrightness(255);
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

void RomanDisplay::printNumber(uint8_t number, uint8_t startIndex, uint8_t sectionLength)
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
                colour = CRGB::Blue;
                break;
            case 'V':
                colour = CRGB::Green;
                break;
            case 'X':
                colour = CRGB::Red;
                break;
            case 'L':
                colour = CRGB::Yellow;
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

void RomanDisplay::clearDisplay()
{
    for (int ix = 0; ix < NUM_LEDS; ix++)
    {
        this->leds[ix] = CRGB(100,120,120);
    }    
}

void RomanDisplay::show()
{
    FastLED.show();
}