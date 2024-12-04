#ifndef bpm_h
#define bpm_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class Bpm : public Pattern
{
public:
    void initialize(LedPatterns ledPatterns)
    {
        ledPatterns.ActivePattern = BPM;
        ledPatterns.TotalSteps = 255;
        ledPatterns.CurrentDirection = NODIR;
    }

    void update(LedPatterns ledPatterns)
    {
        // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
        uint8_t BeatsPerMinute = Interval * 3;
        CRGBPalette16 palette = PartyColors_p;

        uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
            ledPatterns.leds[i] = ColorFromPalette(palette, ledPatterns.Index + (i * 2), beat - ledPatterns.Index + (i * 10));
    }
};
#endif