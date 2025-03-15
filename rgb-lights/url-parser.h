#ifndef URL_PARSER_H
#define URL_PARSER_H

#ifdef ARDUINO
#include "FastLED.h"
#include <Arduino.h>
#else
#include "../tests/mock.h"
#endif

bool isMatch(String path);

#endif
