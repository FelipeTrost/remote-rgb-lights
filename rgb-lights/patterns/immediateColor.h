#ifndef immediateColor_h
#define immediateColor_h

#include "../LedPatterns.h"

class ImmediateColor : public Pattern {
public:
  ImmediateColor(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}
  void update() {
    for (unsigned int i = 0; i < ledPatterns->NUM_LEDS; i++) {
      ledPatterns->setLed(i, ledPatterns->colorsForPatterns[0]);
    }
    FastLED.show(); // need to call it here since we don't return;
    ledPatterns->deleteCurrentPattern();
  }

private:
};
#endif
