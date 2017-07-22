#ifndef CDATChaseEntry_H
#define CDATChaseEntry_H

#include "bxa.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3i8.h"
#include "Type/Vector/CVector3i16.h"
#include "Type/Vector/CVector3D.h"

class bxa::CDATChaseFormat;

class bxa::CDATChaseEntry
{
public:
	CDATChaseEntry(void);
	
	void					unload(void) {}

	void					serialize(void);
	
	void					setFormat(bxa::CDATChaseFormat* pFormat) { m_pFormat = pFormat; }
	bxa::CDATChaseFormat*		getFormat(void) { return m_pFormat; }
	
	void					setVelocity(bxa::CVector3i16& vecVelocity) { m_vecVelocity = vecVelocity; }
	bxa::CVector3i16&			getVelocity(void) { return m_vecVelocity; }

	void					setRight(bxa::CVector3i8& vecRight) { m_vecRight = vecRight; }
	bxa::CVector3i8&				getRight(void) { return m_vecRight; }

	void					setTop(bxa::CVector3i8& vecTop) { m_vecTop = vecTop; }
	bxa::CVector3i8&				getTop(void) { return m_vecTop; }

	void					setSteeringAngle(int8 iSteeringAngle) { m_iSteeringAngle = iSteeringAngle; }
	int8					getSteeringAngle(void) { return m_iSteeringAngle; }

	void					setGasPedalPower(int8 iGasPedalPower) { m_iGasPedalPower = iGasPedalPower; }
	int8					getGasPedalPower(void) { return m_iGasPedalPower; }

	void					setBrakePedalPower(int8 iBrakePedalPower) { m_iBrakePedalPower = iBrakePedalPower; }
	int8					getBrakePedalPower(void) { return m_iBrakePedalPower; }

	void					setHandbrakeUsed(int8 iHandbrakeUsed) { m_iHandbrakeUsed = iHandbrakeUsed; }
	int8					getHandbrakeUsed(void) { return m_iHandbrakeUsed; }

	void					setPosition(bxa::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxa::CVector3D&				getPosition(void) { return m_vecPosition; }
	
private:
	bxa::CDATChaseFormat*		m_pFormat;
	bxa::CVector3i16				m_vecVelocity;
	bxa::CVector3i8				m_vecRight;
	bxa::CVector3i8				m_vecTop;
	int8					m_iSteeringAngle;
	int8					m_iGasPedalPower;
	int8					m_iBrakePedalPower;
	int8					m_iHandbrakeUsed;
	bxa::CVector3D				m_vecPosition;
};

#endif