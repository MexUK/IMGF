#ifndef CIntermediateBoundingObject_H
#define CIntermediateBoundingObject_H

#include "mcore.h"
#include "Type/Types.h"
#include "eIntermediateBoundingObjectType.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"

class mcore::CIntermediateBoundingObject
{
public:
	CIntermediateBoundingObject(void) :
		m_eBoundingObjectType(BOUNDING_OBJECT_TYPE_SPHERE),
		m_fRadius(0.0f),
		m_bHasPositions(false),
		m_bHasNormals(false)
	{
		m_vecMin.m_x = 0.0f;
		m_vecMin.m_y = 0.0f;
		m_vecMin.m_z = 0.0f;
		m_vecMin.m_w = 0.0f;
		m_vecMax.m_x = 0.0f;
		m_vecMax.m_y = 0.0f;
		m_vecMax.m_z = 0.0f;
		m_vecMax.m_w = 0.0f;

		m_vecCenter.m_x = 0.0f;
		m_vecCenter.m_y = 0.0f;
		m_vecCenter.m_z = 0.0f;
	}

	void								setBoundingObjectType(mcore::eIntermediateBoundingObjectType eIntermediateBoundingObjectTypeValue) { m_eBoundingObjectType = eIntermediateBoundingObjectTypeValue; }
	mcore::eIntermediateBoundingObjectType		getBoundingObjectType(void) { return m_eBoundingObjectType; }

	void								setMin(mcore::CVector4D vecMin) { m_vecMin = vecMin; }
	mcore::CVector4D							getMin(void) { return m_vecMin; }

	void								setMax(mcore::CVector4D vecMax) { m_vecMax = vecMax; }
	mcore::CVector4D							getMax(void) { return m_vecMax; }

	void								setCenter(mcore::CVector3D vecCenter) { m_vecCenter = vecCenter; }
	mcore::CVector3D							getCenter(void) { return m_vecCenter; }

	void								setRadius(float32 fRadius) { m_fRadius = fRadius; }
	float32								getRadius(void) { return m_fRadius; }

	void								setHasPositions(bool bHasPositions) { m_bHasPositions = bHasPositions; }
	bool								doesHavePositions(void) { return m_bHasPositions; }

	void								setHasNormals(bool bHasNormals) { m_bHasNormals = bHasNormals; }
	bool								doesHaveNormals(void) { return m_bHasNormals; }

private:
	mcore::eIntermediateBoundingObjectType		m_eBoundingObjectType;
	union
	{
		struct
		{
			mcore::CVector4D					m_vecMin;
			mcore::CVector4D					m_vecMax;
		};
		struct
		{
			mcore::CVector3D					m_vecCenter;
			float32						m_fRadius;
			uint8						m_bHasPositions : 1;
			uint8						m_bHasNormals : 1;
		};
	};
};

#endif