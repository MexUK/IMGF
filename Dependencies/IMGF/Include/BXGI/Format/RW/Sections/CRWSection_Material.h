#pragma once

#include "nsbxgi.h"
#include "Format/RW/CRWSection.h"

class bxgi::CRWSection_Material : public bxgi::CRWSection
{
public:
	CRWSection_Material(void);

	void							unserialize(void);
	void							serialize(void);

	void							setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32							getUnknown1(void) { return m_uiUnknown1; }

	void							setColour(uint32 uiColour) { m_uiColour = uiColour; }
	uint32							getColour(void) { return m_uiColour; }

	void							setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32							getUnknown2(void) { return m_uiUnknown2; }

	void							setUsesTextures(uint32 uiUsesTextures) { m_uiUsesTextures = uiUsesTextures; }
	uint32							getUsesTextures(void) { return m_uiUsesTextures; }

	void							setAmbient(float32 fAmbient) { m_fAmbient = fAmbient; }
	float32							getAmbient(void) { return m_fAmbient; }

	void							setSpecular(float32 fSpecular) { m_fSpecular = fSpecular; }
	float32							getSpecular(void) { return m_fSpecular; }

	void							setDiffuse(float32 fDiffuse) { m_fDiffuse = fDiffuse; }
	float32							getDiffuse(void) { return m_fDiffuse; }

private:
	uint32							m_uiUnknown1;
	uint32							m_uiColour;
	uint32							m_uiUnknown2;
	uint32							m_uiUsesTextures;
	float32							m_fAmbient;
	float32							m_fSpecular;
	float32							m_fDiffuse;
};