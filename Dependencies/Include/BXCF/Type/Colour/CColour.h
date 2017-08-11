#ifndef CColour_H
#define CColour_H

#define _USE_MATH_DEFINES

#include "bxcf.h"
#include "Type/Vector/Vec4u8.h"
#include <math.h>

class bxcf::CColour
{
public:
	uint8	red;
	uint8	green;
	uint8	blue;
	uint8	alpha;

	CColour(void);
	CColour(uint8 uiRed, uint8 uiGreen, uint8 uiBlue, uint8 uiAlpha = 0xFF);

	CColour*				copy(void);

	void					lighten(float32 fMultiplier);
	void					darken(float32 fMultiplier);
};

#endif