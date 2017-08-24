#ifndef CIPLEntry_OCCL_H
#define CIPLEntry_OCCL_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/Vec2f.h"

class bxgi::CIPLEntry_OCCL : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_OCCL(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_OCCL),
		m_vecMidPosition{ 0.0f, 0.0f },
		m_fBottomHeightZ(0.0f),
		m_vecWidth{ 0.0f, 0.0f },
		m_fHeight(0.0f),
		m_fRotation(0.0f),
		m_fUnknown1(0.0f),
		m_fUnknown2(0.0f),
		m_uiUnknown3(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setMidPosition(bxcf::Vec2f& vecMidPosition) { m_vecMidPosition = vecMidPosition; }
	bxcf::Vec2f&					getMidPosition(void) { return m_vecMidPosition; }

	void						setBottomHeightZ(float32 fBottomHeightZ) { m_fBottomHeightZ = fBottomHeightZ; }
	float32						getBottomHeightZ(void) { return m_fBottomHeightZ; }

	void						setWidth(bxcf::Vec2f& vecWidth) { m_vecWidth = vecWidth; }
	bxcf::Vec2f&					getWidth(void) { return m_vecWidth; }

	void						setHeight(float32 fHeight) { m_fHeight = fHeight; }
	float32						getHeight(void) { return m_fHeight; }

	void						setRotation(float32 fRotation) { m_fRotation = fRotation; }
	float32						getRotation(void) { return m_fRotation; }

	void						setUnknown1(float32 fUnknown1) { m_fUnknown1 = fUnknown1; }
	float32						getUnknown1(void) { return m_fUnknown1; }

	void						setUnknown2(float32 fUnknown2) { m_fUnknown2 = fUnknown2; }
	float32						getUnknown2(void) { return m_fUnknown2; }

	void						setUnknown3(uint32 uiUnknown3) { m_uiUnknown3 = uiUnknown3; }
	uint32						getUnknown3(void) { return m_uiUnknown3; }

private:
	// GTA VC only
	bxcf::Vec2f					m_vecMidPosition;
	float32						m_fBottomHeightZ;
	bxcf::Vec2f					m_vecWidth;
	float32						m_fHeight;
	float32						m_fRotation;

	// GTA SA only
	float32						m_fUnknown1;
	float32						m_fUnknown2;
	uint32						m_uiUnknown3;
};

#endif