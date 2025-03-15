#include "mock.h"
#include <chrono>
#include <sys/timeb.h>

int skip = 0;
int millis() {
  using namespace std::chrono;
  auto now = steady_clock::now();
  auto elapsed = duration_cast<milliseconds>(now.time_since_epoch());
  return elapsed.count() + skip;
};

void skipMillis(int ms) { skip += ms; };

void delay(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
  }
}

int random16(int max) { return 0; };
int random8(int max) { return 0; };

_FastLED FastLED;

// FastLED stuff

CRGB CHSV(int hue, int sat, int val) {
  CRGB color;
  color.r = hue;
  color.g = sat;
  color.b = val;
  return color;
}
