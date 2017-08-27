#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4f.h"
#include <string>

class bxgi::CIPLEntry_INST : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_INST(bxgi::CIPLFormat *pIPLFormat);

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

	void						setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&					getPosition(void) { return m_vecPosition; }

	void						setScale(bxcf::Vec3f& vecScale) { m_vecScale = vecScale; }
	bxcf::Vec3f&					getScale(void) { return m_vecScale; }

	void						setRotation(bxcf::Vec4f& vecRotation) { m_vecRotation = vecRotation; }
	bxcf::Vec4f&					getRotation(void) { return m_vecRotation; }

	void						setLOD(int32 iLOD) { m_iLOD = iLOD; }
	int32						getLOD(void) { return m_iLOD; }

private:
	// GTA III era only
	uint32						m_uiObjectId;
	std::string					m_strModelName;
	uint32						m_uiInterior;
	bxcf::Vec3f					m_vecPosition;
	bxcf::Vec3f					m_vecScale;
	bxcf::Vec4f					m_vecRotation;
	int32						m_iLOD;
};