#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2f.h"

class bxgi::DATWaterproEntry
{
public:
	DATWaterproEntry(void);
	
	void					unload(void) {}

	void					setWaterLevel(float32 fWaterLevel) { m_fWaterLevel = fWaterLevel; }
	float32					getWaterLevel(void) { return m_fWaterLevel; }
	
	void					setWaterZoneStart(bxcf::Vec2f& vecWaterZoneStart) { m_vecWaterZoneStart = vecWaterZoneStart; }
	bxcf::Vec2f&				getWaterZoneStart(void) { return m_vecWaterZoneStart; }
	
	void					setWaterZoneEnd(bxcf::Vec2f& vecWaterZoneEnd) { m_vecWaterZoneEnd = vecWaterZoneEnd; }
	bxcf::Vec2f&				setWaterZoneEnd(void) { return m_vecWaterZoneEnd; }
	
private:
	float32					m_fWaterLevel;
	bxcf::Vec2f				m_vecWaterZoneStart;
	bxcf::Vec2f				m_vecWaterZoneEnd;
};