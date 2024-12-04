#ifndef sinePulse_h
#define sinePulse_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class Pulse : public Pattern
{
public:
    void initialize(LedPatterns ledPatterns, uint8_t r, uint8_t g, uint8_t b)
    {
        ledPatterns.ActivePattern = PULSE;
        ledPatterns.CurrentDirection = FORWARDS;
        ledPatterns.TotalSteps = 70;
        ledPatterns.Index = 0;

        R = r;
        G = g;
        B = b;
    }

    void update(LedPatterns ledPatterns)
    {
        uint16_t realIndex = (ledPatterns.Index + 100 - ledPatterns.TotalSteps);
        double m = realIndex / 100.0;

        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
            leds[i] = CRGB(m * R, m * G, m * B);
    }

private:
    uint8_t R, G, B;
};
#endif