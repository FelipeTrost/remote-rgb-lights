#ifndef LedPatterns_h
#define LedPatterns_h

#ifdef ARDUINO
#include "FastLED.h"
#include <Arduino.h>
#else
#include "../tests/mock.h"
#endif

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define MAX_LED_ENTRIES 50
#define COLORS_FOR_PATTERNS 5

// Pattern types supported:
// enum pattern {
//   NONE,
//   SIMPLE_RAINBOW_CYCLE,
//   RAINBOW_CYCLE,
//   THEATER_CHASE,
//   COLOR_WIPE,
//   SCANNER,
//   PULSE,
//   SIMPLE_MUSIC,
//   PACIFICA,
//   FIRE,
//   PRIDE,
//   CYCLON,
//   CONFETTI,
//   BPM,
//   JUGGLE,
//   TWINKLEFOX,
//   SINEPULSE,
//   ICOLOR
// };

// Forward declare the classes
class Pattern;
class LedPatterns;

class Pattern {
protected:
  LedPatterns *ledPatterns;

public:
  Pattern(LedPatterns *lp) { ledPatterns = lp; }
  // // Virtual destructor
  virtual ~Pattern() = default;
  virtual void update() = 0; // Pure virtual method
};

struct ledEntry {
  CRGB *leds;
  unsigned int NUM_LEDS;
};

// NeoPattern Class - derived from the Adafruit_NeoPixel class
class LedPatterns {
public:
  unsigned long long Interval = 30;
  unsigned long long lastUpdate = 0;

  unsigned int NUM_LEDS = 0;
  uint8_t brightness = 100;

  LedPatterns();

  void addLeds(CRGB *leds, unsigned int NUM_LEDS);

  // Update leds
  void setLed(unsigned int i, uint8_t r, uint8_t g, uint8_t b);
  void setLed(unsigned int i, CRGB color);

  void setLed(unsigned int strip, unsigned int i, uint8_t r, uint8_t g,
              uint8_t b);
  void setLed(unsigned int strip, unsigned int i, CRGB color);

  CRGB *getLed(unsigned int strip, int i);
  CRGB *getLed(unsigned int i);

  // Pattern stuff
  void setPattern(Pattern *newPattern);
  void deleteCurrentPattern();

  void setBrightness(uint8_t newBrightness);
  void Update();

  // Just some helper functions to not do everything in a pattern
  void immediateOff();

  // Currently only the first one is used
  CRGB colorsForPatterns[COLORS_FOR_PATTERNS];
  uint8_t colorsForAnimation = 0;

  uint8_t nLedEntries = 0;
  ledEntry ledEntries[MAX_LED_ENTRIES];

  // should be private, but tests wouldn't work (I don't want to do getters and
  // setters, those are for chumps)
  Pattern *activePattern = 0;
};

#endif
