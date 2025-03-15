#ifndef cyclon_h
#define cyclon_h

#include "../LedPatterns.h"

class Cyclon : public Pattern {
public:
  Cyclon(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}

  void update() {
    ledPatterns->setLed(index, CHSV(cyclonhue++, 255, 255));
    fadeall();

    index = (index + 1) % ledPatterns->NUM_LEDS;
    cyclonhue = cyclonhue == 255 ? 0 : cyclonhue + 1;
  }

private:
  uint8_t cyclonhue = 0;
  unsigned int index = 0;

  void fadeall() {
    for (int i = 0; i < ledPatterns->NUM_LEDS; i++) {
      CRGB *color = ledPatterns->getLed(i);
      if (color == (CRGB *)-1)
        continue;

      color->nscale8(250);

      ledPatterns->setLed(i, *color);
    }
  }

  // TWINKLE FOX
};
#endif
