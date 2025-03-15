#include "LedPatterns.h"

void LedPatterns::setPattern(Pattern *newPattern) {
  if (activePattern)
    deleteCurrentPattern();

  activePattern = newPattern;
}

void LedPatterns::deleteCurrentPattern() {
  if (!activePattern)
    return;

  operator delete(activePattern);
  activePattern = 0;
};

LedPatterns::LedPatterns() // void (*callback)()
{}

void LedPatterns::addLeds(CRGB *leds, unsigned int NUM_LEDS) {
  if (nLedEntries == MAX_LED_ENTRIES)
    // NOTE: maybe some error handling
    return;

  if (NUM_LEDS > this->NUM_LEDS)
    this->NUM_LEDS = NUM_LEDS;

  ledEntries[nLedEntries++] = {leds, NUM_LEDS};
}

void LedPatterns::setLed(unsigned int i, uint8_t r, uint8_t g, uint8_t b) {
  for (size_t j = 0; j < nLedEntries; j++) {
    if (i < ledEntries[j].NUM_LEDS) {
      ledEntries[j].leds[i].setRGB(r, g, b);
    }
  }
}
void LedPatterns::setLed(unsigned int strip, unsigned int i, uint8_t r,
                         uint8_t g, uint8_t b) {
  if (strip >= nLedEntries)
    return;
  if (i < ledEntries[strip].NUM_LEDS) {
    ledEntries[strip].leds[i].setRGB(r, g, b);
  }
}

void LedPatterns::setLed(unsigned int i, CRGB color) {
  for (size_t j = 0; j < nLedEntries; j++) {
    if (i < ledEntries[j].NUM_LEDS) {
      ledEntries[j].leds[i] = color;
    }
  }
}
void LedPatterns::setLed(unsigned strip, unsigned int i, CRGB color) {
  if (strip >= nLedEntries)
    return;
  if (i < ledEntries[strip].NUM_LEDS) {
    ledEntries[strip].leds[i] = color;
  }
}

CRGB *LedPatterns::getLed(unsigned int i) {
  for (size_t j = 0; j < nLedEntries; j++) {
    if (i < ledEntries[j].NUM_LEDS) {
      return &(ledEntries[j].leds[i]);
    }
  }
  return (CRGB *)-1;
}

void LedPatterns::setBrightness(uint8_t newBrightness) {
  if (newBrightness >= 0 && newBrightness <= 100)
    brightness = newBrightness;
}

void LedPatterns::Update() {
  if (!activePattern)
    return;

  if ((millis() - lastUpdate) < Interval)
    return;

  lastUpdate = millis();
  activePattern->update();

  FastLED.show();
}

void LedPatterns::immediateOff() {
  this->deleteCurrentPattern();
  for (int i = 0; i < this->NUM_LEDS; i++) {
    this->setLed(i, 0, 0, 0);
  }
  FastLED.show();
}
