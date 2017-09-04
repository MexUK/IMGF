#pragma once

#include "nsbxcf.h"
//#include "D3D8Types.h"

class bxcf::Colour
{
public:
	uint8	red;
	uint8	green;
	uint8	blue;
	uint8	alpha;

	Colour(void);
	Colour(uint8 uiRed, uint8 uiGreen, uint8 uiBlue, uint8 uiAlpha = 0xFF);

	Colour*					copy(void);

	void					lighten(float32 fMultiplier);
	void					darken(float32 fMultiplier);

	//D3DCOLOR				toD3dColor(void);
};