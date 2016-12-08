#ifndef CIPLEntry_INST_H
#define CIPLEntry_INST_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include <string>

class mcore::CIPLEntry_INST : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_INST(mcore::CIPLFormat *pIPLFormat) :
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

	void						setPosition(mcore::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	mcore::CVector3D&					getPosition(void) { return m_vecPosition; }

	void						setScale(mcore::CVector3D& vecScale) { m_vecScale = vecScale; }
	mcore::CVector3D&					getScale(void) { return m_vecScale; }

	void						setRotation(mcore::CVector4D& vecRotation) { m_vecRotation = vecRotation; }
	mcore::CVector4D&					getRotation(void) { return m_vecRotation; }

	void						setLOD(int32 iLOD) { m_iLOD = iLOD; }
	int32						getLOD(void) { return m_iLOD; }

private:
	// GTA III era only
	uint32						m_uiObjectId;
	std::string					m_strModelName;
	uint32						m_uiInterior;
	mcore::CVector3D					m_vecPosition;
	mcore::CVector3D					m_vecScale;
	mcore::CVector4D					m_vecRotation;
	int32						m_iLOD;
};

#endif