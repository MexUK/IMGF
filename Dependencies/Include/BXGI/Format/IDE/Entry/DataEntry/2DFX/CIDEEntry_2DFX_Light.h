#ifndef CIDEEntry_2DFX_Light_H
#define CIDEEntry_2DFX_Light_H

#include "bxgi.h"
#include "Format/IDE/Entry/DataEntry/CIDEEntry_2DFX.h"
#include <string>

class bxgi::CIDEEntry_2DFX_Light : public bxgi::CIDEEntry_2DFX
{
public:
	CIDEEntry_2DFX_Light(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_2DFX(pIDEFormat, bxgi::_2DFX_LIGHT),
		m_fViewDistance(0.0f),
		m_fOuterRange(0.0f),
		m_fCoronaSize(0.0f),
		m_fInnerRange(0.0f),
		m_uiIDEFlag(0),
		m_uiFlash(0),
		m_uiWet(0),
		m_uiFlare(0),
		m_uiDust(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setCoronaTexture(std::string& strCoronaTexture) { m_strCoronaTexture = strCoronaTexture; }
	std::string&				getCoronaTexture(void) { return m_strCoronaTexture; }

	void						setShadowTexture(std::string& strShadowTexture) { m_strShadowTexture = strShadowTexture; }
	std::string&				getShadowTexture(void) { return m_strShadowTexture; }

	void						setViewDistance(float32 fViewDistance) { m_fViewDistance = fViewDistance; }
	float32						getViewDistance(void) { return m_fViewDistance; }

	void						setOuterRange(float32 fOuterRange) { m_fOuterRange = fOuterRange; }
	float32						getOuterRange(void) { return m_fOuterRange; }

	void						setCoronaSize(float32 fCoronaSize) { m_fCoronaSize = fCoronaSize; }
	float32						getCoronaSize(void) { return m_fCoronaSize; }

	void						setInnerRange(float32 fInnerRange) { m_fInnerRange = fInnerRange; }
	float32						getInnerRange(void) { return m_fCoronaSize; }

	void						setIDEFlag(uint32 uiIDEFlag) { m_uiIDEFlag = uiIDEFlag; }
	uint32						getIDEFlag(void) { return m_uiIDEFlag; }

	void						setFlash(uint32 uiFlash) { m_uiFlash = uiFlash; }
	uint32						getFlash(void) { return m_uiFlash; }

	void						setWet(uint32 uiWet) { m_uiWet = uiWet; }
	uint32						getWet(void) { return m_uiWet; }

	void						setFlare(uint32 uiFlare) { m_uiFlare = uiFlare; }
	uint32						getFlare(void) { return m_uiFlare; }

	void						setDust(uint32 uiDust) { m_uiDust = uiDust; }
	uint32						getDust(void) { return m_uiDust; }

private:
	// GTA III era only
	std::string					m_strCoronaTexture;
	std::string					m_strShadowTexture;
	float32						m_fViewDistance;
	float32						m_fOuterRange;
	float32						m_fCoronaSize;
	float32						m_fInnerRange;
	uint32						m_uiIDEFlag;
	uint32						m_uiFlash;
	uint32						m_uiWet;
	uint32						m_uiFlare;
	uint32						m_uiDust;
};

#endif