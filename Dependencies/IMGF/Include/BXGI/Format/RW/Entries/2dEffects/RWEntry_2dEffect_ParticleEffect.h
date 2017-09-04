#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/_2dEffect.h"
#include <string>

// todo - fucking rename to without effect in name

class bxgi::RWEntry_2dEffect_ParticleEffect : public bxgi::_2dEffect
{
public:
	RWEntry_2dEffect_ParticleEffect(void);

	void							unserialize(void);
	void							serialize(void);

	void							setParticleEffectName(std::string& strParticleEffectName) { m_strParticleEffectName = strParticleEffectName; }
	std::string&					getParticleEffectName(void) { return m_strParticleEffectName; }

private:
	std::string						m_strParticleEffectName;
};