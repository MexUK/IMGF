#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4f.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"

class bxgi::CIPLEntry_CULL : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_CULL(bxgi::CIPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32						getFlags(void) { return m_uiFlags; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						setCenterPosition(bxcf::Vec3f& vecCenterPosition) { m_vecCenterPosition = vecCenterPosition; }
	bxcf::Vec3f&					getCenterPosition(void) { return m_vecCenterPosition; }

	void						setLowerLeftPosition(bxcf::Vec3f& vecLowerLeftPosition) { m_vecLowerLeftPosition = vecLowerLeftPosition; }
	bxcf::Vec3f&					getLowerLeftPosition(void) { return m_vecLowerLeftPosition; }

	void						setUpperRightPosition(bxcf::Vec3f& vecUpperRightPosition) { m_vecUpperRightPosition = vecUpperRightPosition; }
	bxcf::Vec3f&					getUpperRightPosition(void) { return m_vecUpperRightPosition; }

	void						setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32						getUnknown2(void) { return m_uiUnknown2; }

	void						setUnknown3(uint32 uiUnknown3) { m_uiUnknown3 = uiUnknown3; }
	uint32						getUnknown3(void) { return m_uiUnknown3; }

	void						setLength(uint32 uiLength) { m_uiLength = uiLength; }
	uint32						getLength(void) { return m_uiLength; }

	void						setWidth(uint32 uiWidth) { m_uiWidth = uiWidth; }
	uint32						getWidth(void) { return m_uiWidth; }

	void						setTop(uint32 uiTop) { m_uiTop = uiTop; }
	uint32						getTop(void) { return m_uiTop; }

	void						setBottom(uint32 uiBottom) { m_uiBottom = uiBottom; }
	uint32						getBottom(void) { return m_uiBottom; }

	void						setMirrorParameters(bxcf::Vec4f& vecMirrorParameters) { m_vecMirrorParameters = vecMirrorParameters; }
	bxcf::Vec4f&					getMirrorParameters(void) { return m_vecMirrorParameters; }

private:
	// GTA III era & GTA IV
	uint32						m_uiFlags;
	uint32						m_uiUnknown1;

	// GTA III era
	bxcf::Vec3f					m_vecCenterPosition;
	bxcf::Vec3f					m_vecLowerLeftPosition;
	bxcf::Vec3f					m_vecUpperRightPosition;

	// GTA SA & GTA IV
	uint32						m_uiUnknown2;
	uint32						m_uiUnknown3;
	uint32						m_uiLength;
	uint32						m_uiWidth;
	uint32						m_uiTop;
	uint32						m_uiBottom;
	bxcf::Vec4f					m_vecMirrorParameters;
};