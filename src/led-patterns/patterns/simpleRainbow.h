
#ifndef simpleRainbow_h
#define simpleRainbow_h

#include "../Pattern.h"
#include "../LedPatterns.h"

class SimpleRainbow : public Pattern
{
public:
	void initialize(LedPatterns ledPatterns)
	{
		ledPatterns.ActivePattern = SIMPLE_RAINBOW_CYCLE;
		ledPatterns.CurrentDirection = NODIR;
		ledPatterns.TotalSteps = 255;
		ledPatterns.Index = 0;
	}

	void update(LedPatterns ledPatterns)
	{
		for (int i = 0; i < ledPatterns.NUM_LEDS; i++)
		{
			uint32_t ret[3];
			Wheel(ret, ((i * 256) + ledPatterns.Index) & 255);
			ledPatterns.leds[i].setRGB(ret[0], ret[1], ret[2]);
		}
	}

private:
	void Wheel(uint32_t ret[3], byte WheelPos)
	{
		WheelPos = 255 - WheelPos;
		if (WheelPos < 85)
		{
			ret[0] = 255 - WheelPos * 3;
			ret[1] = 0;
			ret[2] = WheelPos * 3;
		}
		else if (WheelPos < 170)
		{
			WheelPos -= 85;
			ret[0] = 0;
			ret[1] = WheelPos * 3;
			ret[2] = 255 - WheelPos * 3;
		}
		else
		{
			WheelPos -= 170;
			ret[0] = WheelPos * 3;
			ret[1] = 255 - WheelPos * 3;
			ret[2] = 0;
		}
	}
};
#endif