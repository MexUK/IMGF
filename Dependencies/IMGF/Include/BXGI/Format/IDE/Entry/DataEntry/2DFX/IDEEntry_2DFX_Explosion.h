#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_2DFX.h"

class bxgi::IDEEntry_2DFX_Explosion : public bxgi::IDEEntry_2DFX
{
public:
	IDEEntry_2DFX_Explosion(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32						getUnknown2(void) { return m_uiUnknown2; }

	void						setUnknown3(uint32 uiUnknown3) { m_uiUnknown3 = uiUnknown3; }
	uint32						getUnknown3(void) { return m_uiUnknown3; }

	void						setUnknown4(uint32 uiUnknown4) { m_uiUnknown4 = uiUnknown4; }
	uint32						getUnknown4(void) { return m_uiUnknown4; }

private:
	// GTA IV only
	uint32						m_uiUnknown1;
	uint32						m_uiUnknown2;
	uint32						m_uiUnknown3;
	uint32						m_uiUnknown4;
};