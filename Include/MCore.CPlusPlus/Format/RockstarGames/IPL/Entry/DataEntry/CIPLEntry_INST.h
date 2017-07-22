#ifndef CIPLEntry_INST_H
#define CIPLEntry_INST_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include <string>

class bxa::CIPLEntry_INST : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_INST(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_INST),
		m_uiObjectId(0),
		m_uiInterior(0),
		m_vecPosition{ 0.0f, 0.0f, 0.0f },
		m_vecScale{ 0.0f, 0.0f, 0.0f },
		m_vecRotation{ 0.0f, 0.0f, 0.0f, 0.0f },
		m_iLOD(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						unserialize_Text(void);
	void						unserialize_Binary(void);

	void						serialize_Text(void);
	void						serialize_Binary(void);

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setInterior(uint32 uiInterior) { m_uiInterior = uiInterior; }
	uint32						getInterior(void) { return m_uiInterior; }

	void						setPosition(bxa::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxa::CVector3D&					getPosition(void) { return m_vecPosition; }

	void						setScale(bxa::CVector3D& vecScale) { m_vecScale = vecScale; }
	bxa::CVector3D&					getScale(void) { return m_vecScale; }

	void						setRotation(bxa::CVector4D& vecRotation) { m_vecRotation = vecRotation; }
	bxa::CVector4D&					getRotation(void) { return m_vecRotation; }

	void						setLOD(int32 iLOD) { m_iLOD = iLOD; }
	int32						getLOD(void) { return m_iLOD; }

private:
	// GTA III era only
	uint32						m_uiObjectId;
	std::string					m_strModelName;
	uint32						m_uiInterior;
	bxa::CVector3D					m_vecPosition;
	bxa::CVector3D					m_vecScale;
	bxa::CVector4D					m_vecRotation;
	int32						m_iLOD;
};

#endif