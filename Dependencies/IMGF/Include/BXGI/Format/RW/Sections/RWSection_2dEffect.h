#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"
#include "Format/RW/Pools/_2dEffectsPool.h"

class bxgi::RWSection_2dEffect : public bxgi::RWSection
{
public:
	RWSection_2dEffect(void);
	~RWSection_2dEffect(void);

	void							unserialize(void);
	void							serialize(void);

	bxgi::_2dEffectsPool*			get2dEffects(void) { return m_p2dEffectsPool; }

private:
	bxgi::_2dEffectsPool*			m_p2dEffectsPool;
};