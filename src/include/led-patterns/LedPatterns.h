#ifndef LedPatterns_h
#define LedPatterns_h

#ifdef ARDUINO_VERSION
#include "Arduino.h"
#include "FastLED.h"
#endif

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#include "Pattern.h"

#include "patterns/bpm.h"
#include "patterns/colorWipe.h"
#include "patterns/confetti.h"
#include "patterns/cyclon.h"
#include "patterns/fire.h"
#include "patterns/immediateColor.h"
#include "patterns/juggle.h"
#include "patterns/pacifica.h"
#include "patterns/pride.h"
#include "patterns/pulse.h"
#include "patterns/rainbowCycle.h"
#include "patterns/simpleRainbow.h"
#include "patterns/sinePulse.h"
#include "patterns/twinkleFox.h"

// Pattern types supported:
enum pattern {
  NONE,
  SIMPLE_RAINBOW_CYCLE,
  RAINBOW_CYCLE,
  THEATER_CHASE,
  COLOR_WIPE,
  SCANNER,
  PULSE,
  SIMPLE_MUSIC,
  PACIFICA,
  FIRE,
  PRIDE,
  CYCLON,
  CONFETTI,
  BPM,
  JUGGLE,
  TWINKLEFOX,
  SINEPULSE,
  ICOLOR
};

// directions
enum direction { FORWARDS, BACKWARDS, NODIR, DISABLED };

// NeoPattern Class - derived from the Adafruit_NeoPixel class
class LedPatterns {
public:
  // Member Variables:
  pattern ActivePattern; // which pattern is running
  direction CurrentDirection = NODIR;

  unsigned long long Interval;   // milliseconds between updates
  unsigned long long lastUpdate; // last update of position
  uint16_t Index;                // current step within the pattern
  uint16_t TotalSteps;           // total number of steps in the pattern

  uint16_t Pin;
  CRGB *leds;
  uint16_t NUM_LEDS;
  uint8_t brightness = 100;

  LedPatterns(uint16_t pixels, uint8_t pin) // void (*callback)()
  {
    NUM_LEDS = pixels;
    leds = (CRGB *)malloc(pixels * sizeof(CRGB));
    Pin = pin;
  }

  void setBrightness(uint8_t newBrightness) {
    if (newBrightness >= 0 && newBrightness <= 100)
      brightness = newBrightness;
  }

  void Update() {
    if ((millis() - lastUpdate) < Interval) // time to update
      return;

    lastUpdate = millis();
    activePattern->update(this);

    // Set brightness
    float multiplier = brightness / 100;
    for (size_t i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(leds[i].r * multiplier, leds[i].g * multiplier,
                     leds[i].b * multiplier);
    }

#ifdef ARDUINO_VERSION
    FastLED.show();
#endif
    Increment();
  }

  void Increment() {
    if (CurrentDirection == DISABLED)
      return;

    if (CurrentDirection == NODIR) {
      Index++;
      if (Index >= TotalSteps) {
        Index = 0;
      }
    } else if (CurrentDirection == FORWARDS) {
      Index++;
      if (Index >= TotalSteps) {
        CurrentDirection = BACKWARDS;
      }
    } else if (CurrentDirection == BACKWARDS) {
      --Index;
      if (Index <= 0) {
        CurrentDirection = FORWARDS;
      }
    }
  }

  void startSimplePattern(pattern inputPattern) {
    deleteCurrentPattern();

    switch (inputPattern) {
    case RAINBOW_CYCLE:
      RainbowCycle pattern;
      activePattern = &pattern;
      break;
    case SIMPLE_RAINBOW_CYCLE:
      SimpleRainbow pattern;
      activePattern = &pattern;
      break;
    case PACIFICA:
      Pacifica pattern;
      activePattern = &pattern;
      break;
    case FIRE:
      Fire pattern;
      activePattern = &pattern;
      break;
    case PRIDE:
      Pride pattern;
      activePattern = &pattern;
      break;
    case CYCLON:
      Cyclon pattern;
      activePattern = &pattern;
      break;
    case CONFETTI:
      Confetti pattern;
      activePattern = &pattern;
      break;
    case BPM:
      Bpm pattern;
      activePattern = &pattern;
      break;
    case JUGGLE:
      Juggle pattern;
      activePattern = &pattern;
      break;
    case TWINKLEFOX:
      TwinkleFox pattern;
      activePattern = &pattern;
      break;
    default:
      break;
    }

    activePattern->initialize();
  }

  void colorWipe(uint8_t r, uint8_t g, uint8_t b) {
    deleteCurrentPattern();
    ColorWipe pattern;
    pattern.initializeComplex(this, r, g, b);
    activePattern = &pattern;
  }

  void immediateColor(uint8_t r, uint8_t g, uint8_t b) {
    deleteCurrentPattern();
    ImmediateColor pattern;
    pattern.initializeComplex(this, r, g, b);
    activePattern = &pattern;
  }

  void sinePulse(uint8_t r, uint8_t g, uint8_t b) {
    deleteCurrentPattern();
    SinePulse pattern;
    pattern.initializeComplex(this, r, g, b);
    activePattern = &pattern;
  }

  void simplePulse(uint8_t r, uint8_t g, uint8_t b) {
    deleteCurrentPattern();
    Pulse pattern;
    pattern.initializeComplex(this, r, g, b);
    activePattern = &pattern;
  }

private:
  Pattern *activePattern = null;

  void deleteCurrentPattern() {
    if (activePattern == null)
      return;

    activePattern->destroy();
    operator delete(activePattern)
  }

#endif
