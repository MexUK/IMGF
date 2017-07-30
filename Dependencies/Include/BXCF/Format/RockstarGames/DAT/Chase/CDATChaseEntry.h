#ifndef CDATChaseEntry_H
#define CDATChaseEntry_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3i8.h"
#include "Type/Vector/CVector3i16.h"
#include "Type/Vector/CVector3D.h"

class bxcf::CDATChaseFormat;

class bxcf::CDATChaseEntry
{
public:
	CDATChaseEntry(void);
	
	void					unload(void) {}

	void					serialize(void);
	
	void					setFormat(bxcf::CDATChaseFormat* pFormat) { m_pFormat = pFormat; }
	bxcf::CDATChaseFormat*		getFormat(void) { return m_pFormat; }
	
	void					setVelocity(bxcf::CVector3i16& vecVelocity) { m_vecVelocity = vecVelocity; }
	bxcf::CVector3i16&			getVelocity(void) { return m_vecVelocity; }

	void					setRight(bxcf::CVector3i8& vecRight) { m_vecRight = vecRight; }
	bxcf::CVector3i8&				getRight(void) { return m_vecRight; }

	void					setTop(bxcf::CVector3i8& vecTop) { m_vecTop = vecTop; }
	bxcf::CVector3i8&				getTop(void) { return m_vecTop; }

	void					setSteeringAngle(int8 iSteeringAngle) { m_iSteeringAngle = iSteeringAngle; }
	int8					getSteeringAngle(void) { return m_iSteeringAngle; }

	void					setGasPedalPower(int8 iGasPedalPower) { m_iGasPedalPower = iGasPedalPower; }
	int8					getGasPedalPower(void) { return m_iGasPedalPower; }

	void					setBrakePedalPower(int8 iBrakePedalPower) { m_iBrakePedalPower = iBrakePedalPower; }
	int8					getBrakePedalPower(void) { return m_iBrakePedalPower; }

	void					setHandbrakeUsed(int8 iHandbrakeUsed) { m_iHandbrakeUsed = iHandbrakeUsed; }
	int8					getHandbrakeUsed(void) { return m_iHandbrakeUsed; }

	void					setPosition(bxcf::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::CVector3D&				getPosition(void) { return m_vecPosition; }
	
private:
	bxcf::CDATChaseFormat*		m_pFormat;
	bxcf::CVector3i16				m_vecVelocity;
	bxcf::CVector3i8				m_vecRight;
	bxcf::CVector3i8				m_vecTop;
	int8					m_iSteeringAngle;
	int8					m_iGasPedalPower;
	int8					m_iBrakePedalPower;
	int8					m_iHandbrakeUsed;
	bxcf::CVector3D				m_vecPosition;
};

#endif