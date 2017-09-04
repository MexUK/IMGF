#pragma once

#include "nsbxgi.h"
#include "Format/RW/CRWSection.h"
#include "Format/RW/Pools/C2dEffectsPool.h"

class bxgi::CRWSection_2dEffect : public bxgi::CRWSection
{
public:
	CRWSection_2dEffect(void);
	~CRWSection_2dEffect(void);

	void							unserialize(void);
	void							serialize(void);

	bxgi::C2dEffectsPool*			get2dEffects(void) { return m_p2dEffectsPool; }

private:
	bxgi::C2dEffectsPool*			m_p2dEffectsPool;
};