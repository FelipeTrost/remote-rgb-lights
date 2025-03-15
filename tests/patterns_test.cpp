#include "../rgb-lights/LedPatterns.h"
#include "mock.h"
#include <gtest/gtest.h>

// Patterns
#include "../rgb-lights/patterns/colorWipe.h"
#include "../rgb-lights/patterns/confetti.h"
#include "../rgb-lights/patterns/cyclon.h"
#include "../rgb-lights/patterns/immediateColor.h"
#include "../rgb-lights/patterns/ledStripCycle.h"
#include "../rgb-lights/patterns/rainbowCycle.h"
#include "../rgb-lights/patterns/simpleRainbow.h"

#define UPDATE_ITERATIONS 10000

void drawToTerminal(CRGB *pixels, int n, int width) {
  // std::cout << "\033[H"; // Move cursor to the top-left corner
  for (size_t i = 0; i < n; ++i) {
    const auto &pixel = pixels[i];
    std::cout << "\033[48;2;" << pixel.r << ";" << pixel.g << ";" << pixel.b
              << "m "; // Set background color

    // if ((i + 1) % width == 0) {
    //   std::cout << "\033[0m\n"; // Reset and move to the next line
    // }
  }
  // std::cout << "\033[0m"; // Reset colors at the end
}

void iteratePattern(LedPatterns *ledPatterns, int iterations) {
  for (int i = 0; i < iterations; i++) {
    skipMillis(ledPatterns->Interval);
    ledPatterns->Update();
  }
}

CRGB leds1[10];
CRGB leds2[100];
CRGB leds3[1000];
CRGB leds4[10000];

// macro to create ledpatterns
#define CREATE_LEDPATTERNS()                                                   \
  LedPatterns ledPatterns;                                                     \
  ledPatterns.addLeds(leds1, 10);                                              \
  ledPatterns.addLeds(leds2, 100);                                             \
  ledPatterns.addLeds(leds3, 1000);                                            \
  ledPatterns.addLeds(leds4, 10000);

// Demonstrate some basic assertions.
TEST(TestPatternUpdates, ConfettiPattern) {
  CREATE_LEDPATTERNS();

  ledPatterns.setPattern(new Confetti(&ledPatterns));

  EXPECT_NO_THROW(iteratePattern(&ledPatterns, UPDATE_ITERATIONS));
}

TEST(TestPatternUpdates, ColorWipePattern) {
  CREATE_LEDPATTERNS();

  ledPatterns.setPattern(new ColorWipe(&ledPatterns, 255, 100, 0));

  EXPECT_NO_THROW(iteratePattern(&ledPatterns, 10000 + 1));
  EXPECT_EQ(ledPatterns.activePattern, (Pattern *)0);
}

TEST(TestPatternUpdates, ImmediateColor) {
  CREATE_LEDPATTERNS();
  ledPatterns.setPattern(new ImmediateColor(&ledPatterns, 255, 100, 0));

  EXPECT_NO_THROW(iteratePattern(&ledPatterns, UPDATE_ITERATIONS));
  EXPECT_EQ(ledPatterns.activePattern, (Pattern *)0);
}

TEST(TestPatternUpdates, SimpleRainbow) {
  CREATE_LEDPATTERNS();
  ledPatterns.setPattern(new SimpleRainbow(&ledPatterns));

  EXPECT_NO_THROW(iteratePattern(&ledPatterns, UPDATE_ITERATIONS));
}

TEST(TestPatternUpdates, RainbowCycle) {
  CREATE_LEDPATTERNS();
  ledPatterns.setPattern(new RainbowCycle(&ledPatterns));

  EXPECT_NO_THROW(iteratePattern(&ledPatterns, UPDATE_ITERATIONS));
}

TEST(TestPatternUpdates, LedStripCycle) {
  CREATE_LEDPATTERNS();
  ledPatterns.setPattern(new LedStripCycle(&ledPatterns));

  EXPECT_NO_THROW(iteratePattern(&ledPatterns, UPDATE_ITERATIONS));
}

TEST(TestPatternUpdates, Cyclon) {
  CREATE_LEDPATTERNS();
  ledPatterns.setPattern(new Cyclon(&ledPatterns));

  EXPECT_NO_THROW(iteratePattern(&ledPatterns, UPDATE_ITERATIONS));
}
