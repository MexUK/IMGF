#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"
#include "Format/E2DFXType.h"
#include "Type/Vector/Vec3u.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4f.h"
#include <string>

class bxgi::CIDEEntry_2DFX : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_2DFX(bxgi::CIDEFormat *pIDEFormat, bxgi::E2DFXType E2DFXTypeValue);
	~CIDEEntry_2DFX(void);

	virtual void				unserialize(void);
	virtual void				serialize(void);

	void						set2DFXType(bxgi::E2DFXType E2DFXTypeValue) { m_E2DFXType = E2DFXTypeValue; }
	bxgi::E2DFXType					get2DFXType(void) { return m_E2DFXType; }

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&					getPosition(void) { return m_vecPosition; }

	void						setColour(bxcf::Vec3u& vecColour) { m_vecColour = vecColour; }
	bxcf::Vec3u&				getColour(void) { return m_vecColour; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						set2dfxType(uint32 ui2dfxType) { m_ui2dfxType = ui2dfxType; }
	uint32						get2dfxType(void) { return m_ui2dfxType; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setRotation(bxcf::Vec4f& vecRotation) { m_vecRotation = vecRotation; }
	bxcf::Vec4f&					getRotation(void) { return m_vecRotation; }

private:
	bxgi::E2DFXType					m_E2DFXType;
	bxcf::Vec3f					m_vecPosition; // GTA III era + GTA IV
	uint32						m_ui2dfxType; // GTA III era + GTA IV
	union
	{
		struct // GTA III era only
		{
			uint32						m_uiObjectId;
			bxcf::Vec3u				m_vecColour;
			uint32						m_uiUnknown1;
		};
		struct // GTA IV only
		{
			std::string					m_strModelName;
			bxcf::Vec4f					m_vecRotation;
		};
	};
};