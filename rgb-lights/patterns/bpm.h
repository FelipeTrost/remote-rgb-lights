#ifndef bpm_h
#define bpm_h

#include "../LedPatterns.h"

class Bpm : public Pattern {
public:
  Bpm(LedPatterns *ledPatterns) : Pattern(ledPatterns) {}

  void update() {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = ledPatterns->Interval * 3;
    CRGBPalette16 palette = PartyColors_p;

    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < ledPatterns->NUM_LEDS; i++) {
      CRGB color =
          ColorFromPalette(palette, index + (i * 2), beat - index + (i * 10));
      ledPatterns->setLed(i, color);
    }
  }

  uint8_t index = 60;
};
#endif
