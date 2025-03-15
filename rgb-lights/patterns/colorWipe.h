#ifndef colorWipe_h
#define colorWipe_h

#include "../LedPatterns.h"
#include <iostream>

class ColorWipe : public Pattern {
public:
  ColorWipe(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}
  void update() {
    if (index >= ledPatterns->NUM_LEDS)
      return ledPatterns->deleteCurrentPattern();

    ledPatterns->setLed(index++, ledPatterns->colorsForPatterns[0]);
  }

private:
  unsigned int index = 0;
};
#endif
