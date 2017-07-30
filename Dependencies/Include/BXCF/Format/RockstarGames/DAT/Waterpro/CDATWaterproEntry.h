#ifndef CDATWaterproEntry_H
#define CDATWaterproEntry_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/CVector2D.h"

class bxcf::CDATWaterproEntry
{
public:
	CDATWaterproEntry(void);
	
	void					unload(void) {}

	void					setWaterLevel(float32 fWaterLevel) { m_fWaterLevel = fWaterLevel; }
	float32					getWaterLevel(void) { return m_fWaterLevel; }
	
	void					setWaterZoneStart(bxcf::CVector2D& vecWaterZoneStart) { m_vecWaterZoneStart = vecWaterZoneStart; }
	bxcf::CVector2D&				getWaterZoneStart(void) { return m_vecWaterZoneStart; }
	
	void					setWaterZoneEnd(bxcf::CVector2D& vecWaterZoneEnd) { m_vecWaterZoneEnd = vecWaterZoneEnd; }
	bxcf::CVector2D&				setWaterZoneEnd(void) { return m_vecWaterZoneEnd; }
	
private:
	float32					m_fWaterLevel;
	bxcf::CVector2D				m_vecWaterZoneStart;
	bxcf::CVector2D				m_vecWaterZoneEnd;
};

#endif