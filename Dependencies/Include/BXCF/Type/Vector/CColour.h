#ifndef CColour_H
#define CColour_H

#define _USE_MATH_DEFINES

#include "bxcf.h"
#include "Type/Vector/CVector4ui8.h"
#include <math.h>

class bxcf::CColour
{
private:
	uint8	m_x;
	uint8	m_y;
	uint8	m_z;
	uint8	m_w;

public:
	CColour(void);
	CColour(uint8 uiRed, uint8 uiGreen, uint8 uiBlue, uint8 uiAlpha = 0xFF);

	uint8					red(void) { return m_x; }
	uint8					green(void) { return m_y; }
	uint8					blue(void) { return m_z; }
	uint8					alpha(void) { return m_w; }
};

#endif