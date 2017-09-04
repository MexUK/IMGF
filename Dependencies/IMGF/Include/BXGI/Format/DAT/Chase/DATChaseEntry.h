#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3i8.h"
#include "Type/Vector/Vec3i16.h"
#include "Type/Vector/Vec3f.h"

class bxgi::DATChaseFormat;

class bxgi::DATChaseEntry
{
public:
	DATChaseEntry(void);
	
	void					unload(void) {}

	void					serialize(void);
	
	void					setFormat(bxgi::DATChaseFormat* pFormat) { m_pFormat = pFormat; }
	bxgi::DATChaseFormat*		getFormat(void) { return m_pFormat; }
	
	void					setVelocity(bxcf::Vec3i16& vecVelocity) { m_vecVelocity = vecVelocity; }
	bxcf::Vec3i16&			getVelocity(void) { return m_vecVelocity; }

	void					setRight(bxcf::Vec3i8& vecRight) { m_vecRight = vecRight; }
	bxcf::Vec3i8&				getRight(void) { return m_vecRight; }

	void					setTop(bxcf::Vec3i8& vecTop) { m_vecTop = vecTop; }
	bxcf::Vec3i8&				getTop(void) { return m_vecTop; }

	void					setSteeringAngle(int8 iSteeringAngle) { m_iSteeringAngle = iSteeringAngle; }
	int8					getSteeringAngle(void) { return m_iSteeringAngle; }

	void					setGasPedalPower(int8 iGasPedalPower) { m_iGasPedalPower = iGasPedalPower; }
	int8					getGasPedalPower(void) { return m_iGasPedalPower; }

	void					setBrakePedalPower(int8 iBrakePedalPower) { m_iBrakePedalPower = iBrakePedalPower; }
	int8					getBrakePedalPower(void) { return m_iBrakePedalPower; }

	void					setHandbrakeUsed(int8 iHandbrakeUsed) { m_iHandbrakeUsed = iHandbrakeUsed; }
	int8					getHandbrakeUsed(void) { return m_iHandbrakeUsed; }

	void					setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&				getPosition(void) { return m_vecPosition; }
	
private:
	bxgi::DATChaseFormat*		m_pFormat;
	bxcf::Vec3i16				m_vecVelocity;
	bxcf::Vec3i8				m_vecRight;
	bxcf::Vec3i8				m_vecTop;
	int8					m_iSteeringAngle;
	int8					m_iGasPedalPower;
	int8					m_iBrakePedalPower;
	int8					m_iHandbrakeUsed;
	bxcf::Vec3f				m_vecPosition;
};