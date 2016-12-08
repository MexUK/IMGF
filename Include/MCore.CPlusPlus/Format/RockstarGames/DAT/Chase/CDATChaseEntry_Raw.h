#ifndef CDATChaseEntry_Raw_H
#define CDATChaseEntry_Raw_H

#include "mcore.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3i8.h"
#include "Type/Vector/CVector3i16.h"
#include "Type/Vector/CVector3D.h"

#pragma pack(push, 1)
struct mcore::CDATChaseEntry_Raw
{
	mcore::CVector3i16				m_vecVelocity;
	mcore::CVector3i8				m_vecRight;
	mcore::CVector3i8				m_vecTop;
	int8					m_iSteeringAngle;
	int8					m_iGasPedalPower;
	int8					m_iBrakePedalPower;
	int8					m_iHandbrakeUsed;
	mcore::CVector3D				m_vecPosition;
};
#pragma pack(pop)

#endif