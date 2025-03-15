#ifndef sinePulse_h
#define sinePulse_h

#include "../LedPatterns.h"
#define TOTAL_STEPS 314 * 2

class SinePulse : public Pattern {
public:
  SinePulse(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}
  SinePulse(LedPatterns *ledPatterns, CRGB color) : Pattern(ledPatterns) {}

  void update() {
    double m = (sin((6.28 / 3.14) * (index / 100.0)) + 1.0) / 2.0;

    CRGB target = ledPatterns->colorsForPatterns[0];
    CRGB color = CRGB(target.r, target.g, target.b).setHue(m);
    for (int i = 0; i < ledPatterns->NUM_LEDS; i++)
      ledPatterns->setLed(index, color);
  }

private:
  uint8_t index = 0;
};
#endif
