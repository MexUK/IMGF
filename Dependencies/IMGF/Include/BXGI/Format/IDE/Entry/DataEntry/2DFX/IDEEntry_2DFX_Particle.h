#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_2DFX.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec3u.h"
#include <string>

class bxgi::IDEEntry_2DFX_Particle : public bxgi::IDEEntry_2DFX
{
public:
	IDEEntry_2DFX_Particle(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setParticleType(uint32 uiParticleType) { m_uiParticleType = uiParticleType; }
	uint32						getParticleType(void) { return m_uiParticleType; }

	void						setStrength(bxcf::Vec3f& vecStrength) { m_vecStrength = vecStrength; }
	bxcf::Vec3f&					getStrength(void) { return m_vecStrength; }

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

	void						setColour2(bxcf::Vec3u& vecColour2) { m_vecColour2 = vecColour2; }
	bxcf::Vec3u&				getColour2(void) { return m_vecColour2; }

private:
	// GTA III era & GTA IV
	float32						m_fSize;

	// GTA III era only
	uint32						m_uiParticleType;
	bxcf::Vec3f					m_vecStrength;

	// GTA IV only
	std::string					m_strParticleName;
	uint32						m_uiDestructionStageCount;
	uint32						m_uiDrawDistance;
	uint32						m_uiUnknown2;
	uint32						m_uiUnknown3;
	bxcf::Vec3u				m_vecColour2;
};