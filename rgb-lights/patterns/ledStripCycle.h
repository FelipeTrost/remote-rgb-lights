#ifndef ledStripCyle_h
#define ledStripCyle_h

#include "../LedPatterns.h"

class LedStripCycle : public Pattern {
public:
  LedStripCycle(LedPatterns *ledPatterns) : Pattern(ledPatterns) {
    this->speed = 1;
  }
  LedStripCycle(LedPatterns *ledPatterns, uint8_t speed)
      : Pattern(ledPatterns) {
    this->speed = speed;
  }

  void update() {
    float circleStep = 360.0 / ledPatterns->nLedEntries;

    int firstPoint = floor(angle / circleStep);
    int second = ((int)ceil(angle / circleStep)) % ledPatterns->nLedEntries;
    float travel = (angle - firstPoint * circleStep) / circleStep;

    int firstPointIntensity = 255 * (1 - travel);
    int secondPointIntensity = 255 * travel;

    CRGB t = ledPatterns->colorsForPatterns[0];

    for (int strip = 0; strip < ledPatterns->nLedEntries; strip++) {
      int intensity = 0;

      if (strip == firstPoint) {
        intensity = firstPointIntensity;
      } else if (strip == second) {
        intensity = secondPointIntensity;
      }

      for (int i = 0; i < ledPatterns->ledEntries[strip].NUM_LEDS; i++) {
        ledPatterns->setLed(strip, i, t.r * intensity, t.g * intensity,
                            t.g * intensity);
      }
    }

    angle = (angle + speed) % 360;
  }

private:
  uint16_t angle;
  uint16_t speed = 0;
};
#endif
