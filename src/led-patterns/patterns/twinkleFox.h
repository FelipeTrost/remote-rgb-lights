#ifndef twinkleFox_h
#define twinkleFox_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class TwinkleFox : public Pattern
{
public:
    void initialize(LedPatterns ledPatterns)
    {
        ledPatterns.ActivePattern = TWINKLEFOX;
        ledPatterns.TotalSteps = 100;
        ledPatterns.CurrentDirection = DISABLED;

        chooseNextColorPalette(gTargetPalette);
    }

    void update(LedPatterns ledPatterns)
    {
        if (millis() - twinkle_last_chosen >= SECONDS_PER_PALETTE * 1000)
        {
            chooseNextColorPalette(gTargetPalette);
            twinkle_last_chosen = millis();
        }

        nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, 12);
        drawTwinkles();
    }

private:
    uint8_t TWINKLE_SPEED = 4;
    uint8_t TWINKLE_DENSITY = 5;
    uint8_t SECONDS_PER_PALETTE = 30;
    CRGB gBackgroundColor = CRGB::Black;
    bool COOL_LIKE_INCANDESCENT = true;
    unsigned long int twinkle_last_chosen = 0;

    void drawTwinkles(LedPatterns ledPatterns)
    {
        uint16_t PRNG16 = 11337;

        uint32_t clock32 = millis();
        CRGB bg = gBackgroundColor; // just use the explicitly defined background color

        uint8_t backgroundBrightness = bg.getAverageLight();

        for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
        {
            PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
            uint16_t myclockoffset16 = PRNG16;         // use that number as clock offset
            PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
            // use that number as clock speed adjustment factor (in 8ths, from 8/8ths to 23/8ths)
            uint8_t myspeedmultiplierQ5_3 = ((((PRNG16 & 0xFF) >> 4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
            uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
            uint8_t myunique8 = PRNG16 >> 8; // get 'salt' value for this pixel

            CRGB c = computeOneTwinkle(myclock30, myunique8);

            uint8_t cbright = c.getAverageLight();
            int16_t deltabright = cbright - backgroundBrightness;
            if (deltabright >= 32 || (!bg))
            {
                ledPatterns.leds[i] = c;
            }
            else if (deltabright > 0)
            {
                ledPatterns.leds[i] = blend(bg, c, deltabright * 8);
            }
            else
            {
                ledPatterns.leds[i] = bg;
            }
        }
    }

    CRGB computeOneTwinkle(uint32_t ms, uint8_t salt)
    {
        uint16_t ticks = ms >> (8 - TWINKLE_SPEED);
        uint8_t fastcycle8 = ticks;
        uint16_t slowcycle16 = (ticks >> 8) + salt;
        slowcycle16 += sin8(slowcycle16);
        slowcycle16 = (slowcycle16 * 2053) + 1384;
        uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);

        uint8_t bright = 0;
        if (((slowcycle8 & 0x0E) / 2) < TWINKLE_DENSITY)
        {
            bright = attackDecayWave8(fastcycle8);
        }

        uint8_t hue = slowcycle8 - salt;
        CRGB c;
        if (bright > 0)
        {
            c = ColorFromPalette(gCurrentPalette, hue, bright, NOBLEND);
            if (COOL_LIKE_INCANDESCENT == 1)
            {
                coolLikeIncandescent(c, fastcycle8);
            }
        }
        else
        {
            c = CRGB::Black;
        }
        return c;
    }

    CRGBPalette16 gCurrentPalette;
    CRGBPalette16 gTargetPalette;

    uint8_t attackDecayWave8(uint8_t i)
    {
        if (i < 86)
        {
            return i * 3;
        }
        else
        {
            i -= 86;
            return 255 - (i + (i / 2));
        }
    }

    void coolLikeIncandescent(CRGB &c, uint8_t phase)
    {
        if (phase < 128)
            return;

        uint8_t cooling = (phase - 128) >> 4;
        c.g = qsub8(c.g, cooling);
        c.b = qsub8(c.b, cooling * 2);
    }

    // A mostly red palette with green accents and white trim.
    // "CRGB::Gray" is used as white to keep the brightness more uniform.
    const TProgmemRGBPalette16 RedGreenWhite_p FL_PROGMEM =
        {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
         CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
         CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray,
         CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green};

// A mostly (dark) green palette with red berries.
#define Holly_Green 0x00580c
#define Holly_Red 0xB00402
    const TProgmemRGBPalette16 Holly_p FL_PROGMEM =
        {Holly_Green, Holly_Green, Holly_Green, Holly_Green,
         Holly_Green, Holly_Green, Holly_Green, Holly_Green,
         Holly_Green, Holly_Green, Holly_Green, Holly_Green,
         Holly_Green, Holly_Green, Holly_Green, Holly_Red};

    // A red and white striped palette
    // "CRGB::Gray" is used as white to keep the brightness more uniform.
    const TProgmemRGBPalette16 RedWhite_p FL_PROGMEM =
        {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
         CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
         CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
         CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray};

    // A mostly blue palette with white accents.
    // "CRGB::Gray" is used as white to keep the brightness more uniform.
    const TProgmemRGBPalette16 BlueWhite_p FL_PROGMEM =
        {CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
         CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
         CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
         CRGB::Blue, CRGB::Gray, CRGB::Gray, CRGB::Gray};

// A pure "fairy light" palette with some brightness variations
#define HALFFAIRY ((CRGB::FairyLight & 0xFEFEFE) / 2)
#define QUARTERFAIRY ((CRGB::FairyLight & 0xFCFCFC) / 4)
    const TProgmemRGBPalette16 FairyLight_p FL_PROGMEM =
        {CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight,
         HALFFAIRY, HALFFAIRY, CRGB::FairyLight, CRGB::FairyLight,
         QUARTERFAIRY, QUARTERFAIRY, CRGB::FairyLight, CRGB::FairyLight,
         CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight};

    // A palette of soft snowflakes with the occasional bright one
    const TProgmemRGBPalette16 Snow_p FL_PROGMEM =
        {0x304048, 0x304048, 0x304048, 0x304048,
         0x304048, 0x304048, 0x304048, 0x304048,
         0x304048, 0x304048, 0x304048, 0x304048,
         0x304048, 0x304048, 0x304048, 0xE0F0FF};

// A palette reminiscent of large 'old-school' C9-size tree lights
// in the five classic colors: red, orange, green, blue, and white.
#define C9_Red 0xB80400
#define C9_Orange 0x902C02
#define C9_Green 0x046002
#define C9_Blue 0x070758
#define C9_White 0x606820
    const TProgmemRGBPalette16 RetroC9_p FL_PROGMEM =
        {C9_Red, C9_Orange, C9_Red, C9_Orange,
         C9_Orange, C9_Red, C9_Orange, C9_Red,
         C9_Green, C9_Green, C9_Green, C9_Green,
         C9_Blue, C9_Blue, C9_Blue,
         C9_White};

// A cold, icy pale blue palette
#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
    const TProgmemRGBPalette16 Ice_p FL_PROGMEM =
        {
            Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
            Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
            Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
            Ice_Blue2, Ice_Blue2, Ice_Blue2, Ice_Blue3};

    // Add or remove palette names from this list to control which color
    // palettes are used, and in what order.
    const TProgmemRGBPalette16 *ActivePaletteList[10] = {
        &RetroC9_p,
        &BlueWhite_p,
        &RainbowColors_p,
        &FairyLight_p,
        &RedGreenWhite_p,
        &PartyColors_p,
        &RedWhite_p,
        &Snow_p,
        &Holly_p,
        &Ice_p};

    // Advance to the next color palette in the list (above).
    void chooseNextColorPalette(CRGBPalette16 &pal)
    {
        const uint8_t numberOfPalettes = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);
        static uint8_t whichPalette = -1;
        whichPalette = addmod8(whichPalette, 1, numberOfPalettes);

        pal = *(ActivePaletteList[whichPalette]);
    }
};
}
;
#endif