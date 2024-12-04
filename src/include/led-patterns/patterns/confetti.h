#ifndef confetti_h
#define confetti_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class Confetti : public Pattern
{
public:
    void initialize(LedPatterns ledPatterns)
    {
        ledPatterns.ActivePattern = CONFETTI;
        ledPatterns.TotalSteps = 255;
        ledPatterns.CurrentDirection = NODIR;
    }

    void update(LedPatterns ledPatterns)
    {
        // random colored speckles that blink in and fade smoothly
        fadeall();

        int pos = random16(ledPatterns.NUM_LEDS);
        ledPatterns.leds[pos] += CHSV(ledPatterns.Index + random8(64), 200, 255);
    }
};
#endif