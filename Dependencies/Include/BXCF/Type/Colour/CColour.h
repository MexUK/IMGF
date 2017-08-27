#pragma once

#include "nsbxcf.h"

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