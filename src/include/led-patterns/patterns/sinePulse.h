#ifndef sinePulse_h
#define sinePulse_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class SinePulse : public Pattern
{
public:
    void initializeComplex(LedPatterns ledPatterns, uint8_t r, uint8_t g, uint8_t b)
    {
        ledPatterns.ActivePattern = SINPULSE;
        ledPatterns.CurrentDirection = NODIR;
        ledPatterns.TotalSteps = 314 * 2;
        ledPatterns.Index = 0;

        R = r;
        G = g;
        B = b;
    }

    void update(LedPatterns ledPatterns)
    {
        double m = (sin((6.28 / 3.14) * (Index / 100.0)) + 1.0) / 2.0;

        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
            ledPatterns.leds[i] = CRGB(m * R, m * G, m * B);
    }

private:
    uint8_t R, G, B;
};
#endif