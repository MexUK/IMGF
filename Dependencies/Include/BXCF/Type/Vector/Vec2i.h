#pragma once

#include "bxcf.h"
#include "Type/Types.h"

class bxcf::Vec2i
{
public:
	int32	x;
	int32	y;

	Vec2i(void)
	{
	}

	Vec2i(int32 x, int32 y) :
		x(x),
		y(y)
	{
	}

	Vec2i		operator+(const Vec2i& vecVector2)
	{
		Vec2i vecVector;
		vecVector.x = x + vecVector2.x;
		vecVector.y = y + vecVector2.y;
		return vecVector;
	}

	Vec2i		operator-(const Vec2i& vecVector2)
	{
		Vec2i vecVector;
		vecVector.x = x - vecVector2.x;
		vecVector.y = y - vecVector2.y;
		return vecVector;
	}

	Vec2i		operator/(const bxcf::Vec2i& vecVector2)
	{
		Vec2i vecVector;
		vecVector.x = x / vecVector2.x;
		vecVector.y = y / vecVector2.y;
		return vecVector;
	}

	Vec2i		operator/(const int32 iValue)
	{
		Vec2i vecVector;
		vecVector.x = x / iValue;
		vecVector.y = y / iValue;
		return vecVector;
	}

	Vec2i		operator+=(const bxcf::Vec2i& vecVector2)
	{
		Vec2i vecVector;
		vecVector.x = x + vecVector2.x;
		vecVector.y = y + vecVector2.y;
		return vecVector;
	}
};