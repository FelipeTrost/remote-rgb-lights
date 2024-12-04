#ifndef colorWipe_h
#define colorWipe_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class ColorWipe : public Pattern
{
public:
    void initializeComplex(LedPatterns ledPatterns, uint8_t r, uint8_t g, uint8_t b)
    {
        R = r;
        G = g;
        B = b;

        ledPatterns.CurrentDirection = NODIR;
        ledPatterns.TotalSteps = NUM_LEDS;
        ledPatterns.ActivePattern = COLOR_WIPE;
        ledPatterns.Index = 0;
    }

    void update(LedPatterns ledPatterns)
    {
        ledPatterns.leds[ledPatterns.Index].setRGB(R, G, B);
    }

private:
    uint8_t R, G, B;
};
#endif