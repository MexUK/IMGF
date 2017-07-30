#ifndef CIDEEntry_ANIM_H
#define CIDEEntry_ANIM_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include <string>

class bxcf::CIDEEntry_ANIM : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_ANIM(bxcf::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_ANIM),
		m_uiObjectId(0),
		m_fDrawDistance(0.0f),
		m_uiFlags(0),
		m_uiUnknown1(0),
		m_vecBoundingBoxLowerLeftCorner{ 0.0f, 0.0f, 0.0f },
		m_vecBoundingBoxUpperRightCorner{ 0.0f, 0.0f, 0.0f },
		m_vecBoundingSphereCenterPosition{ 0.0f, 0.0f, 0.0f },
		m_fBoundingSphereRadius(0.0f)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }
	
	void						setTXDName(std::string& strTXDName) { m_strTXDName = strTXDName; }
	std::string&				getTXDName(void) { return m_strTXDName; }

	void						setAnimationName(std::string& strAnimationName) { m_strAnimationName = strAnimationName; }
	std::string&				getAnimationName(void) { return m_strAnimationName; }

	void						setDrawDistance(float32 fDrawDistance) { m_fDrawDistance = fDrawDistance; }
	float32						getDrawDistance(void) { return m_fDrawDistance; }

	void						setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32						getFlags(void) { return m_uiFlags; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						setBoundingBoxLowerLeftCorner(bxcf::CVector3D& vecBoundingBoxLowerLeftCorner) { m_vecBoundingBoxLowerLeftCorner = vecBoundingBoxLowerLeftCorner; }
	bxcf::CVector3D&					getBoundingBoxLowerLeftCorner(void) { return m_vecBoundingBoxLowerLeftCorner; }

	void						setBoundingBoxUpperRightCorner(bxcf::CVector3D& vecBoundingBoxUpperRightCorner) { m_vecBoundingBoxUpperRightCorner = vecBoundingBoxUpperRightCorner; }
	bxcf::CVector3D&					getBoundingBoxUpperRightCorner(void) { return m_vecBoundingBoxUpperRightCorner; }

	void						setBoundingSphereCenterPosition(bxcf::CVector3D& vecBoundingSphereCenterPosition) { m_vecBoundingSphereCenterPosition = vecBoundingSphereCenterPosition; }
	bxcf::CVector3D&					getBoundingSphereCenterPosition(void) { return m_vecBoundingSphereCenterPosition; }

	void						setBoundingSphereRadius(float32 fBoundingSphereRadius) { m_fBoundingSphereRadius = fBoundingSphereRadius; }
	float32						getBoundingSphereRadius(void) { return m_fBoundingSphereRadius; }

	void						setLODModel(std::string& strLODModel) { m_strLODModel = strLODModel; }
	std::string&				getLODModel(void) { return m_strLODModel; }

private:
	// GTA III era & GTA IV
	std::string					m_strModelName;
	std::string					m_strTXDName;
	std::string					m_strAnimationName;
	float32						m_fDrawDistance;
	uint32						m_uiFlags;

	// GTA III era only
	uint32						m_uiObjectId;

	// GTA IV only
	uint32						m_uiUnknown1;
	bxcf::CVector3D					m_vecBoundingBoxLowerLeftCorner;
	bxcf::CVector3D					m_vecBoundingBoxUpperRightCorner;
	bxcf::CVector3D					m_vecBoundingSphereCenterPosition;
	float32						m_fBoundingSphereRadius;
	std::string					m_strLODModel;
};

#endif