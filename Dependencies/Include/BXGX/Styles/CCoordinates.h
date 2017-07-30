#pragma once

#include "Type/Types.h"
#include <string>
#include <vector>

class CCoordinate
{
public:
	union
	{
		float32		m_fRelativeValue;
		int32		m_iAbsoluteValue;
	};
	uint8			m_bIsAbsolute		: 1;
	uint8			m_ucAlignment		: 2; // 0=left, 1=right, 2=center

	void			unserialize(std::string strCoordinateText);

	float32			getCoordinate(uint32 uiAxisHighestValue, uint32 uiTextLength);
};

class CCoordinateWithSign
{
public:
	CCoordinate		m_coord;
	uint8			m_bSignIsPositive	: 1;
};

class CCoordinateExpression
{
public:
	CCoordinate							m_firstCoord;
	std::vector<CCoordinateWithSign>	m_coords;

	CCoordinateExpression(void);
	CCoordinateExpression(std::string strCoordinateExpressionText);

	void								unserialize(std::string strCoordinateExpressionText);

	float32								computeCoordinate(bool bAxisIsX, uint32 uiTextLength = 0);
};