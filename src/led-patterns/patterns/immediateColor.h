#ifndef immediateColor_h
#define immediateColor_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class ImmediateColor : public Pattern
{
public:
    void initializeComplex(LedPatterns ledPatterns, uint8_t r, uint8_t g, uint8_t b)
    {
        ledPatterns.ActivePattern = ICOLOR;
        ledPatterns.Direction = DISABLED;

        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
            ledPatterns.leds[i] = CRGB(r, g, b);
    }

    void update(LedPatterns ledPatterns)
    {
    }
};
#endif