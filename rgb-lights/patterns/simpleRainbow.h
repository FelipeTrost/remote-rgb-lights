
#ifndef simpleRainbow_h
#define simpleRainbow_h

#include "../LedPatterns.h"

class SimpleRainbow : public Pattern {
public:
  SimpleRainbow(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}

  void update() {
    for (int i = 0; i < ledPatterns->NUM_LEDS; i++) {
      uint32_t ret[3];
      Wheel(ret, ((i * 256) + index++) & 255);
      ledPatterns->setLed(i, ret[0], ret[1], ret[2]);
    }
  }

private:
  uint8_t index = 0;
  void Wheel(uint32_t ret[3], uint8_t WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
      ret[0] = 255 - WheelPos * 3;
      ret[1] = 0;
      ret[2] = WheelPos * 3;
    } else if (WheelPos < 170) {
      WheelPos -= 85;
      ret[0] = 0;
      ret[1] = WheelPos * 3;
      ret[2] = 255 - WheelPos * 3;
    } else {
      WheelPos -= 170;
      ret[0] = WheelPos * 3;
      ret[1] = 255 - WheelPos * 3;
      ret[2] = 0;
    }
  }
};
#endif
