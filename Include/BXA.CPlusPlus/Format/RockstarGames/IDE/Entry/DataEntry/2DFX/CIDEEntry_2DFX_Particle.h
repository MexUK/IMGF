#ifndef CIDEEntry_2DFX_Particle_H
#define CIDEEntry_2DFX_Particle_H

#include "BXA.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector3ui32.h"
#include <string>

class bxa::CIDEEntry_2DFX_Particle : public bxa::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Particle(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxa::_2DFX_PARTICLE),
		m_uiParticleType(0),
		m_fSize(0.0f),
		m_uiDestructionStageCount(0),
		m_uiDrawDistance(0),
		m_uiUnknown2(0),
		m_uiUnknown3(0)
	{
		m_vecColour2.m_x = 0;
		m_vecColour2.m_y = 0;
		m_vecColour2.m_z = 0;
	};

	void						unserialize(void);
	void						serialize(void);

	void						setParticleType(uint32 uiParticleType) { m_uiParticleType = uiParticleType; }
	uint32						getParticleType(void) { return m_uiParticleType; }

	void						setStrength(bxa::CVector3D& vecStrength) { m_vecStrength = vecStrength; }
	bxa::CVector3D&					getStrength(void) { return m_vecStrength; }

	void						setSize(float32 fSize) { m_fSize = fSize; }
	float32						getSize(void) { return m_fSize; }

	void						setParticleName(std::string& strParticleName) { m_strParticleName = strParticleName; }
	std::string&				getParticleName(void) { return m_strParticleName; }

	void						setDestructionStageCount(uint32 uiDestructionStageCount) { m_uiDestructionStageCount = uiDestructionStageCount; }
	uint32						getDestructionStageCount(void) { return m_uiDestructionStageCount; }

	void						setDrawDistance(uint32 uiDrawDistance) { m_uiDrawDistance = uiDrawDistance; }
	uint32						getDrawDistance(void) { return m_uiDrawDistance; }

	void						setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32						getUnknown2(void) { return m_uiUnknown2; }

	void						setUnknown3(uint32 uiUnknown3) { m_uiUnknown3 = uiUnknown3; }
	uint32						getUnknown3(void) { return m_uiUnknown3; }

	void						setColour2(bxa::CVector3ui32& vecColour2) { m_vecColour2 = vecColour2; }
	bxa::CVector3ui32&				getColour2(void) { return m_vecColour2; }

private:
	// GTA III era & GTA IV
	float32						m_fSize;

	// GTA III era only
	uint32						m_uiParticleType;
	bxa::CVector3D					m_vecStrength;

	// GTA IV only
	std::string					m_strParticleName;
	uint32						m_uiDestructionStageCount;
	uint32						m_uiDrawDistance;
	uint32						m_uiUnknown2;
	uint32						m_uiUnknown3;
	bxa::CVector3ui32				m_vecColour2;
};

#endif