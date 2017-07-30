#ifndef CDATChaseEntry_Raw_H
#define CDATChaseEntry_Raw_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3i8.h"
#include "Type/Vector/CVector3i16.h"
#include "Type/Vector/CVector3D.h"

#pragma pack(push, 1)
struct bxcf::CDATChaseEntry_Raw
{
	bxcf::CVector3i16				m_vecVelocity;
	bxcf::CVector3i8				m_vecRight;
	bxcf::CVector3i8				m_vecTop;
	int8					m_iSteeringAngle;
	int8					m_iGasPedalPower;
	int8					m_iBrakePedalPower;
	int8					m_iHandbrakeUsed;
	bxcf::CVector3D				m_vecPosition;
};
#pragma pack(pop)

#endif