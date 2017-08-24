#ifndef CIDEEntry_2DFX_Ped_H
#define CIDEEntry_2DFX_Ped_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/Vec3f.h"

class bxgi::CIDEEntry_2DFX_Ped : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Ped(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_PED),
		m_uiBehaviour(0),
		m_vecUnknown2{ 0.0f, 0.0f, 0.0f },
		m_vecPedRotation{ 0.0f, 0.0f, 0.0f }
	{
	};

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

#endif