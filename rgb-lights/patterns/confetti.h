#ifndef confetti_h
#define confetti_h

#include "../LedPatterns.h"
#include <cstdint>

class Confetti : public Pattern {
public:
  Confetti(LedPatterns *ledPatterns) : Pattern(ledPatterns) {
    cooldown = new uint16_t[ledPatterns->NUM_LEDS];
  }

  void update() {
    int col = (loop / (1500 / 30)) % 3;
    // loop++;

    fadeall();

    for (int strip = 0; strip < ledPatterns->nLedEntries; strip++) {
      // random activation for few leds
      if (ledPatterns->NUM_LEDS < 40 && random16(30) > 22)
        continue;

      int pos = random16(ledPatterns->ledEntries[strip].NUM_LEDS);
      if (cooldown[pos] > 0) {
        continue;
      }

      CRGB color = *ledPatterns->getLed(pos);
      ledPatterns->setLed(strip, pos, color + CHSV(random8(64), 200, 255));
      cooldown[pos] = random8(30) + 20;
    }

    for (int i = 0; i < ledPatterns->NUM_LEDS; i++) {
      if (cooldown[i] > 0) {
        cooldown[i]--;
      }
    }
  }

  ~Confetti() { delete[] cooldown; }

private:
  uint8_t loop = 0;
  uint8_t cyclonhue = 0;
  uint16_t *cooldown;
  void fadeall() {
    for (int i = 0; i < ledPatterns->NUM_LEDS; i++) {
      CRGB *color = ledPatterns->getLed(i);
      if (color == (CRGB *)-1)
        continue;

      color->nscale8(250);

      ledPatterns->setLed(i, *color);
    }
  }
};
#endif
