#ifndef CDATWaterproEntry_H
#define CDATWaterproEntry_H

#include "mcore.h"
#include "Type/Types.h"
#include "Type/Vector/CVector2D.h"

class mcore::CDATWaterproEntry
{
public:
	CDATWaterproEntry(void);
	
	void					unload(void) {}

	void					setWaterLevel(float32 fWaterLevel) { m_fWaterLevel = fWaterLevel; }
	float32					getWaterLevel(void) { return m_fWaterLevel; }
	
	void					setWaterZoneStart(mcore::CVector2D& vecWaterZoneStart) { m_vecWaterZoneStart = vecWaterZoneStart; }
	mcore::CVector2D&				getWaterZoneStart(void) { return m_vecWaterZoneStart; }
	
	void					setWaterZoneEnd(mcore::CVector2D& vecWaterZoneEnd) { m_vecWaterZoneEnd = vecWaterZoneEnd; }
	mcore::CVector2D&				setWaterZoneEnd(void) { return m_vecWaterZoneEnd; }
	
private:
	float32					m_fWaterLevel;
	mcore::CVector2D				m_vecWaterZoneStart;
	mcore::CVector2D				m_vecWaterZoneEnd;
};

#endif