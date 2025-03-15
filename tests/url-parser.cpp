#include "../rgb-lights/url-parser.h"
#include <gtest/gtest.h>

TEST(TestPatternUpdates, ConfettiPattern) { EXPECT_EQ(isMatch("rfb"), 0); }
