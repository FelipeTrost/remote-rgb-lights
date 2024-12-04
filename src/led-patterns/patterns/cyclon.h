#ifndef cyclon_h
#define cyclon_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class Cyclon : public Pattern
{
public:
    void initialize(LedPatterns ledPatterns)
    {
        ledPatterns.ActivePattern = CYCLON;
        ledPatterns.TotalSteps = NUM_LEDS;
        ledPatterns.CurrentDirection = FORWARDS;
    }

    void update(LedPatterns ledPatterns)
    {
        // Set the i'th led to red
        ledPatterns.leds[ledPatterns.Index] = CHSV(cyclonhue++, 255, 255);
        // Show the leds
        // FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        fadeall(ledPatterns);
        // Wait a little bit before we loop around and do it again

        // Increment();
    }

private:
    uint8_t cyclonhue = 0;
    void fadeall(LedPatterns ledPatterns)
    {
        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
        {
            ledPatterns.leds[i].nscale8(250);
        }
    }

    // TWINKLE FOX
};
#endif