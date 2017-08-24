#ifndef CIntermediateBoundingObject_H
#define CIntermediateBoundingObject_H

#include "bxgi.h"
#include "Type/Types.h"
#include "eIntermediateBoundingObjectType.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4f.h"

class bxgi::CIntermediateBoundingObject
{
public:
	CIntermediateBoundingObject(void) :
		m_eBoundingObjectType(BOUNDING_OBJECT_TYPE_SPHERE),
		m_fRadius(0.0f),
		m_bHasPositions(false),
		m_bHasNormals(false)
	{
		m_vecMin.x = 0.0f;
		m_vecMin.y = 0.0f;
		m_vecMin.z = 0.0f;
		m_vecMin.w = 0.0f;
		m_vecMax.x = 0.0f;
		m_vecMax.y = 0.0f;
		m_vecMax.z = 0.0f;
		m_vecMax.w = 0.0f;

		m_vecCenter.x = 0.0f;
		m_vecCenter.y = 0.0f;
		m_vecCenter.z = 0.0f;
	}

	void								setBoundingObjectType(bxgi::eIntermediateBoundingObjectType eIntermediateBoundingObjectTypeValue) { m_eBoundingObjectType = eIntermediateBoundingObjectTypeValue; }
	bxgi::eIntermediateBoundingObjectType		getBoundingObjectType(void) { return m_eBoundingObjectType; }

	void								setMin(bxcf::Vec4f vecMin) { m_vecMin = vecMin; }
	bxcf::Vec4f							getMin(void) { return m_vecMin; }

	void								setMax(bxcf::Vec4f vecMax) { m_vecMax = vecMax; }
	bxcf::Vec4f							getMax(void) { return m_vecMax; }

	void								setCenter(bxcf::Vec3f vecCenter) { m_vecCenter = vecCenter; }
	bxcf::Vec3f							getCenter(void) { return m_vecCenter; }

	void								setRadius(float32 fRadius) { m_fRadius = fRadius; }
	float32								getRadius(void) { return m_fRadius; }

	void								setHasPositions(bool bHasPositions) { m_bHasPositions = bHasPositions; }
	bool								doesHavePositions(void) { return m_bHasPositions; }

	void								setHasNormals(bool bHasNormals) { m_bHasNormals = bHasNormals; }
	bool								doesHaveNormals(void) { return m_bHasNormals; }

private:
	bxgi::eIntermediateBoundingObjectType		m_eBoundingObjectType;
	union
	{
		struct
		{
			bxcf::Vec4f					m_vecMin;
			bxcf::Vec4f					m_vecMax;
		};
		struct
		{
			bxcf::Vec3f					m_vecCenter;
			float32						m_fRadius;
			uint8						m_bHasPositions : 1;
			uint8						m_bHasNormals : 1;
		};
	};
};

#endif