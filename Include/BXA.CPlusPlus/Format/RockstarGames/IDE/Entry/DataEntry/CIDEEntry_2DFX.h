#ifndef CIDEEntry_2DFX_H
#define CIDEEntry_2DFX_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"
#include "Format/RockstarGames/e2DFXType.h"
#include "Type/Vector/CVector3ui32.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include <string>

class bxa::CIDEEntry_2DFX : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_2DFX(bxa::CIDEFormat *pIDEFormat, bxa::e2DFXType e2DFXTypeValue) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_2DFX),
		m_e2DFXType(e2DFXTypeValue),
		m_uiObjectId(0),
		m_vecPosition{ 0.0f, 0.0f, 0.0f },
		m_uiUnknown1(0),
		m_ui2dfxType(0),
		m_vecRotation{ 0.0f, 0.0f, 0.0f, 0.0f }
	{
		m_vecColour.m_x = 0;
		m_vecColour.m_y = 0;
		m_vecColour.m_z = 0;
	}
	~CIDEEntry_2DFX(void)
	{
	}

	virtual void				unserialize(void);
	virtual void				serialize(void);

	void						set2DFXType(bxa::e2DFXType e2DFXTypeValue) { m_e2DFXType = e2DFXTypeValue; }
	bxa::e2DFXType					get2DFXType(void) { return m_e2DFXType; }

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setPosition(bxa::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxa::CVector3D&					getPosition(void) { return m_vecPosition; }

	void						setColour(bxa::CVector3ui32& vecColour) { m_vecColour = vecColour; }
	bxa::CVector3ui32&				getColour(void) { return m_vecColour; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						set2dfxType(uint32 ui2dfxType) { m_ui2dfxType = ui2dfxType; }
	uint32						get2dfxType(void) { return m_ui2dfxType; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setRotation(bxa::CVector4D& vecRotation) { m_vecRotation = vecRotation; }
	bxa::CVector4D&					getRotation(void) { return m_vecRotation; }

private:
	bxa::e2DFXType					m_e2DFXType;
	bxa::CVector3D					m_vecPosition; // GTA III era + GTA IV
	uint32						m_ui2dfxType; // GTA III era + GTA IV
	union
	{
		struct // GTA III era only
		{
			uint32						m_uiObjectId;
			bxa::CVector3ui32				m_vecColour;
			uint32						m_uiUnknown1;
		};
		struct // GTA IV only
		{
			std::string					m_strModelName;
			bxa::CVector4D					m_vecRotation;
		};
	};
};

#endif