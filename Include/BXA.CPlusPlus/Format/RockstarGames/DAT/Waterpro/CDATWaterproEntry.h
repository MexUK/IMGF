#ifndef CDATWaterproEntry_H
#define CDATWaterproEntry_H

#include "BXA.h"
#include "Type/Types.h"
#include "Type/Vector/CVector2D.h"

class bxa::CDATWaterproEntry
{
public:
	CDATWaterproEntry(void);
	
	void					unload(void) {}

	void					setWaterLevel(float32 fWaterLevel) { m_fWaterLevel = fWaterLevel; }
	float32					getWaterLevel(void) { return m_fWaterLevel; }
	
	void					setWaterZoneStart(bxa::CVector2D& vecWaterZoneStart) { m_vecWaterZoneStart = vecWaterZoneStart; }
	bxa::CVector2D&				getWaterZoneStart(void) { return m_vecWaterZoneStart; }
	
	void					setWaterZoneEnd(bxa::CVector2D& vecWaterZoneEnd) { m_vecWaterZoneEnd = vecWaterZoneEnd; }
	bxa::CVector2D&				setWaterZoneEnd(void) { return m_vecWaterZoneEnd; }
	
private:
	float32					m_fWaterLevel;
	bxa::CVector2D				m_vecWaterZoneStart;
	bxa::CVector2D				m_vecWaterZoneEnd;
};

#endif