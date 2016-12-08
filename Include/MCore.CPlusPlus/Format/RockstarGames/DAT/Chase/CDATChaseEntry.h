#ifndef CDATChaseEntry_H
#define CDATChaseEntry_H

#include "mcore.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3i8.h"
#include "Type/Vector/CVector3i16.h"
#include "Type/Vector/CVector3D.h"

class mcore::CDATChaseFormat;

class mcore::CDATChaseEntry
{
public:
	CDATChaseEntry(void);
	
	void					unload(void) {}

	void					serialize(void);
	
	void					setFormat(mcore::CDATChaseFormat* pFormat) { m_pFormat = pFormat; }
	mcore::CDATChaseFormat*		getFormat(void) { return m_pFormat; }
	
	void					setVelocity(mcore::CVector3i16& vecVelocity) { m_vecVelocity = vecVelocity; }
	mcore::CVector3i16&			getVelocity(void) { return m_vecVelocity; }

	void					setRight(mcore::CVector3i8& vecRight) { m_vecRight = vecRight; }
	mcore::CVector3i8&				getRight(void) { return m_vecRight; }

	void					setTop(mcore::CVector3i8& vecTop) { m_vecTop = vecTop; }
	mcore::CVector3i8&				getTop(void) { return m_vecTop; }

	void					setSteeringAngle(int8 iSteeringAngle) { m_iSteeringAngle = iSteeringAngle; }
	int8					getSteeringAngle(void) { return m_iSteeringAngle; }

	void					setGasPedalPower(int8 iGasPedalPower) { m_iGasPedalPower = iGasPedalPower; }
	int8					getGasPedalPower(void) { return m_iGasPedalPower; }

	void					setBrakePedalPower(int8 iBrakePedalPower) { m_iBrakePedalPower = iBrakePedalPower; }
	int8					getBrakePedalPower(void) { return m_iBrakePedalPower; }

	void					setHandbrakeUsed(int8 iHandbrakeUsed) { m_iHandbrakeUsed = iHandbrakeUsed; }
	int8					getHandbrakeUsed(void) { return m_iHandbrakeUsed; }

	void					setPosition(mcore::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	mcore::CVector3D&				getPosition(void) { return m_vecPosition; }
	
private:
	mcore::CDATChaseFormat*		m_pFormat;
	mcore::CVector3i16				m_vecVelocity;
	mcore::CVector3i8				m_vecRight;
	mcore::CVector3i8				m_vecTop;
	int8					m_iSteeringAngle;
	int8					m_iGasPedalPower;
	int8					m_iBrakePedalPower;
	int8					m_iHandbrakeUsed;
	mcore::CVector3D				m_vecPosition;
};

#endif