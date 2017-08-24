#ifndef CRWEntry_2dEffect_EnterExit_H
#define CRWEntry_2dEffect_EnterExit_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/C2dEffect.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include <string>

class bxgi::CRWEntry_2dEffect_EnterExit : public bxgi::C2dEffect
{
public:
	CRWEntry_2dEffect_EnterExit(void);

	void							unserialize(void);
	void							serialize(void);

	void							setEnterMarkerRotationAngle(float32 fEnterMarkerRotationAngle) { m_fEnterMarkerRotationAngle = fEnterMarkerRotationAngle; }
	float32							getEnterMarkerRotationAngle(void) { return m_fEnterMarkerRotationAngle; }

	void							setMarkerApporximationRadius(bxcf::Vec2f& vecMarkerApporximationRadius) { m_vecMarkerApporximationRadius = vecMarkerApporximationRadius; }
	bxcf::Vec2f&						getMarkerApporximationRadius(void) { return m_vecMarkerApporximationRadius; }

	void							setExitMarkerPosition(bxcf::Vec3f& vecExitMarkerPosition) { m_vecExitMarkerPosition = vecExitMarkerPosition; }
	bxcf::Vec3f&						getExitMarkerPosition(void) { return m_vecExitMarkerPosition; }

	void							setExitMarkerAngleRotation(float32 fExitMarkerAngleRotation) { m_fExitMarkerAngleRotation = fExitMarkerAngleRotation; }
	float32							getExitMarkerAngleRotation(void) { return m_fExitMarkerAngleRotation; }

	void							setInteriorCount(int32 iInteriorCount) { m_iInteriorCount = iInteriorCount; }
	int32							getInteriorCount(void) { return m_iInteriorCount; }

	void							setFlags(int32 iFlags) { m_iFlags = iFlags; }
	int32							getFlags(void) { return m_iFlags; }
	
	void							setInteriorName(std::string& strInteriorName) { m_strInteriorName = strInteriorName; }
	std::string&					getInteriorName(void) { return m_strInteriorName; }

	void							setSkyColour(int32 iSkyColour) { m_iSkyColour = iSkyColour; }
	int32							getSkyColour(void) { return m_iSkyColour; }

private:
	float32							m_fEnterMarkerRotationAngle; // -marker(relative to the object) (Always 0 ? )
	bxcf::Vec2f						m_vecMarkerApporximationRadius; // The radius of the approximation to the marker X and Y
	bxcf::Vec3f						m_vecExitMarkerPosition; // The position of exit - marker(offset relative to the object) (Always 0 ? )
	float32							m_fExitMarkerAngleRotation; // Rotation exit - marker(relative to the object) (always 0 ? )
	int32							m_iInteriorCount; // Number of interior
	int32							m_iFlags;
	std::string						m_strInteriorName; // -The name of the interior
	int32							m_iSkyColour; // color of the sky
};

#endif