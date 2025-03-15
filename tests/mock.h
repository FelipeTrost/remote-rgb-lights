#ifndef Mock_h
#define Mock_h

// Arduino stuff

// #include "../build/_deps/arduinofake-src/src/WString.h"
#include <cmath>
#include <cstdint> // For desktop/test environments
#include <stdlib.h>

int millis();
void skipMillis(int ms);
int random16(int max);
int random8(int max);

// FastLED stuff
class _FastLED {
public:
  static void show() {}
};
extern _FastLED FastLED;

class CRGB {
public:
  CRGB(uint8_t r, uint8_t g, uint8_t b) {}
  CRGB setHue(uint8_t hue) { return *this; }
  uint8_t r;
  uint8_t g;
  uint8_t b;
  void setRGB(uint8_t r, uint8_t g, uint8_t b) { return; };
  void nscale8(uint8_t value) { return; };
  CRGB operator+(CRGB color) { return color; };
};

CRGB CHSV(int hue, int sat, int val);

#define null 0;
#endif
