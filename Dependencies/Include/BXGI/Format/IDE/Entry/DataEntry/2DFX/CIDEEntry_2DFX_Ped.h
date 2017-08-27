#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/Vec3f.h"

class bxgi::CIDEEntry_2DFX_Ped : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Ped(bxgi::CIDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setBehaviour(uint32 uiBehaviour) { m_uiBehaviour = uiBehaviour; }
	uint32						getBehaviour(void) { return m_uiBehaviour; }

	void						setUnknown2(bxcf::Vec3f& vecUnknown2) { m_vecUnknown2 = vecUnknown2; }
	bxcf::Vec3f&					getUnknown2(void) { return m_vecUnknown2; }

	void						setPedRotation(bxcf::Vec3f& vecPedRotation) { m_vecPedRotation = vecPedRotation; }
	bxcf::Vec3f&					getPedRotation(void) { return m_vecPedRotation; }

private:
	// GTA III era only
	uint32						m_uiBehaviour;
	bxcf::Vec3f					m_vecUnknown2;
	bxcf::Vec3f					m_vecPedRotation;
};