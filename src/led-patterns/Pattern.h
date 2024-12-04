
#include "LedPatterns.h"
#ifndef Pattern_h
#define Pattern_h

class LedPatterns;

class Pattern
{
public:
    virtual void initialize(LedPatterns ledPatterns){return;};
    virtual void update(LedPatterns ledPatterns);
    virtual void destroy(){return;};
};

#endif
