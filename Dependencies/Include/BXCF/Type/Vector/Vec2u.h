#pragma once

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"

class bxcf::Vec2u
{
public:
	uint32	x;
	uint32	y;

public:
	Vec2u(void)
	{
	}

	Vec2u(uint32 x, uint32 y) :
		x(x),
		y(y)
	{
	}

	Vec2u		operator+(const Vec2u& vecVector2)
	{
		Vec2u vecVector;
		vecVector.x = x + vecVector2.x;
		vecVector.y = y + vecVector2.y;
		return vecVector;
	}

	Vec2u		operator+(const bxcf::Vec2i& vecVector2)
	{
		Vec2u vecVector;
		vecVector.x = x + vecVector2.x;
		vecVector.y = y + vecVector2.y;
		return vecVector;
	}

	Vec2u		operator+=(const Vec2u& vecVector2)
	{
		Vec2u vecVector;
		vecVector.x = x + vecVector2.x;
		vecVector.y = y + vecVector2.y;
		return vecVector;
	}

	bxcf::Vec2i		operator-(const Vec2u& vecVector2)
	{
		bxcf::Vec2i vecVector;
		vecVector.x = (int32)x - (int32)vecVector2.x;
		vecVector.y = (int32)y - (int32)vecVector2.y;
		return vecVector;
	}
};