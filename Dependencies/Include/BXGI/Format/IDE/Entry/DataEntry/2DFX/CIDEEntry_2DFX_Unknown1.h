#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/Vec3f.h"

class bxgi::CIDEEntry_2DFX_Unknown1 : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Unknown1(bxgi::CIDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32						getUnknown2(void) { return m_uiUnknown2; }

	void						setUnknown3(bxcf::Vec3f& vecUnknown3) { m_vecUnknown3 = vecUnknown3; }
	bxcf::Vec3f&					getUnknown3(void) { return m_vecUnknown3; }

	void						setUnknown4(uint32 uiUnknown4) { m_uiUnknown4 = uiUnknown4; }
	uint32						getUnknown4(void) { return m_uiUnknown4; }

private:
	// GTA III era only
	uint32						m_uiUnknown2;
	bxcf::Vec3f					m_vecUnknown3;
	uint32						m_uiUnknown4;
};