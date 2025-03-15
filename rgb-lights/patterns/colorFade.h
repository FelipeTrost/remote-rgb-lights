#ifndef colorFade_h
#define colorFade_h

#include "../LedPatterns.h"
#include <cstdint>
#include <iostream>

class ColorFade : public Pattern {
public:
  ColorFade(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}
  ColorFade(LedPatterns *ledPatterns, float speed) : Pattern(ledPatterns) {
    this->speed = speed;
  }
  void update() {

    bool allLedsComplete = true;
    CRGB target = ledPatterns->colorsForPatterns[0];
    const float flat = 10.0;

    for (int i = 0; i < ledPatterns->NUM_LEDS; i++) {
      CRGB *ledColor = ledPatterns->getLed(i);

      float diff_r = abs(ledColor->r - target.r);
      float factor_r = exp(-diff_r * speed) / flat;
      int _r = ceil(ledColor->r + ((target.r - ledColor->r) * factor_r));
      uint8_t r = max(0, min(255, _r));

      float diff_g = abs(ledColor->g - target.g);
      float factor_g = exp(-diff_g / 255) / flat;
      int _g = ledColor->g + ((target.g - ledColor->g) * factor_g);
      uint8_t g = max(0, min(255, _g));

      float diff_b = abs(ledColor->b - target.b);
      float factor_b = exp(-diff_b * speed) / flat;
      int _b = ledColor->b + ((target.b - ledColor->b) * factor_b);
      uint8_t b = max(0, min(255, _b));

      ledPatterns->setLed(i, CRGB(r, g, b));
      allLedsComplete &= (1 == factor_r) && (1 == factor_g) && (1 == factor_b);
    }

    if (allLedsComplete)
      return ledPatterns->deleteCurrentPattern();
  }

private:
  float speed = 0.0000004;
  // 1.0 / 255.0;
};
#endif
