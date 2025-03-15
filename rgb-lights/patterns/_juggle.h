#ifndef juggle_h
#define juggle_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class Juggle : public Pattern
{
public:
    void initialize(LedPatterns ledPatterns)
    {
        ledPatterns.ActivePattern = JUGGLE;
        Interval = interval;
        ledPatterns.TotalSteps = 100;
        ledPatterns.CurrentDirection = NODIR;
    }

    void update(LedPatterns LedPatterns)
    {
        // eight colored dots, weaving in and out of sync with each other
        fadeToBlackBy(ledPatterns.leds, ledPatterns.NUM_LEDS, 20);
        byte dothue = 0;
        for (int i = 0; i < 8; i++)
        {
            ledPatterns.leds[beatsin16(i + 7, 0, ledPatterns.NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
            dothue += 32;
        }
    }
};
#endif