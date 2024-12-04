#ifndef Fire_h
#define Fire_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class Fire : public Pattern
{
public:
    void initialize(LedPatterns ledPatterns)
    {
        heat = (byte *)malloc(LedPatterns.NUM_LEDS * sizeof(byte));
        ledPatterns.ActivePattern = FIRE;
        ledPatterns.CurrentDirection = DISABLED;
        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
            ledPatterns.heat[i] = 0;
    }

    void update(LedPatterns ledPatterns)
    {
        // Step 1.  Cool down every cell a little
        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
        {
            heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / ledPatterns.NUM_LEDS) + 2));
        }

        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for (int k = ledPatterns.NUM_LEDS - 1; k >= 2; k--)
        {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
        }

        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if (random8() < sparking)
        {
            int y = random8(7);
            heat[y] = qadd8(heat[y], random8(160, 255));
        }

        // Step 4.  Map from heat cells to LED colors
        for (int j = 0; j < ledPatterns.NUM_LEDS; j++)
        {
            CRGB color = HeatColor(heat[j]);
            int pixelnumber;
            if (gReverseDirection)
            {
                pixelnumber = (NUM_LEDS - 1) - j;
            }
            else
            {
                pixelnumber = j;
            }
            // fix color (grb -> rgb)
            uint8_t r = color[0];
            color[0] = color[1];
            color[1] = r;

            ledPatterns.leds[pixelnumber] = color;
        }
    }

private:
    uint8_t cooling = 55;
    uint8_t sparking = 120;
    bool gReverseDirection;
    byte heat[];
};
#endif