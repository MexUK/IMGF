#ifndef CDATChaseEntry_Raw_H
#define CDATChaseEntry_Raw_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3i8.h"
#include "Type/Vector/Vec3i16.h"
#include "Type/Vector/Vec3f.h"

#pragma pack(push, 1)
struct bxgi::CDATChaseEntry_Raw
{
	bxcf::Vec3i16				m_vecVelocity;
	bxcf::Vec3i8				m_vecRight;
	bxcf::Vec3i8				m_vecTop;
	int8					m_iSteeringAngle;
	int8					m_iGasPedalPower;
	int8					m_iBrakePedalPower;
	int8					m_iHandbrakeUsed;
	bxcf::Vec3f				m_vecPosition;
};
#pragma pack(pop)

#endif