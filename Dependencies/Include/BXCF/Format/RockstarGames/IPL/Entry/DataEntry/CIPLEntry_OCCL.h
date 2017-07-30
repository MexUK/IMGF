#ifndef CIPLEntry_OCCL_H
#define CIPLEntry_OCCL_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector2D.h"

class bxcf::CIPLEntry_OCCL : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_OCCL(bxcf::CIPLFormat *pIPLFormat) :
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

	void						setMidPosition(bxcf::CVector2D& vecMidPosition) { m_vecMidPosition = vecMidPosition; }
	bxcf::CVector2D&					getMidPosition(void) { return m_vecMidPosition; }

	void						setBottomHeightZ(float32 fBottomHeightZ) { m_fBottomHeightZ = fBottomHeightZ; }
	float32						getBottomHeightZ(void) { return m_fBottomHeightZ; }

	void						setWidth(bxcf::CVector2D& vecWidth) { m_vecWidth = vecWidth; }
	bxcf::CVector2D&					getWidth(void) { return m_vecWidth; }

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
	bxcf::CVector2D					m_vecMidPosition;
	float32						m_fBottomHeightZ;
	bxcf::CVector2D					m_vecWidth;
	float32						m_fHeight;
	float32						m_fRotation;

	// GTA SA only
	float32						m_fUnknown1;
	float32						m_fUnknown2;
	uint32						m_uiUnknown3;
};

#endif