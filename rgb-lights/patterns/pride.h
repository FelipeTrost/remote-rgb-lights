#ifndef pride_h
#define pride_h

#include "../LedPatterns.h"

class Pride : public Pattern {
public:
  Pride(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}

  void update() {
    uint16_t hue16 = sHue16; // gHue * 256;

    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis;
    sLastMillis = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88(400, 5, 9);
    uint16_t brightnesstheta16 = sPseudotime;

    for (uint16_t i = 0; i < ledPatterns->NUM_LEDS; i++) {
      hue16 += hueinc16;
      uint8_t hue8 = hue16 / 256;

      brightnesstheta16 += brightnessthetainc16;
      uint16_t b16 = sin16(brightnesstheta16) + 32768;

      uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
      uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
      bri8 += (255 - brightdepth);

      CRGB newcolor = CHSV(hue8, sat8, bri8);

      uint16_t pixelnumber = (ledPatterns->NUM_LEDS - 1) - i;

      CRGB n = nblend(*ledPatterns->getLed(i), newcolor, 64);
      ledPatterns->setLed(i, n);
    }
  }

private:
  const uint8_t sat8 = beatsin88(87, 220, 250);
  const uint8_t brightdepth = beatsin88(341, 96, 224);
  const uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
  const uint8_t msmultiplier = beatsin88(147, 23, 60);
  const uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t sPseudotime = 0;
  uint16_t sLastMillis = 0;
  uint16_t sHue16 = 0;
};
#endif
