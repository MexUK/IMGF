#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "EIntermediateBoundingObjectType.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4f.h"

class bxgi::IntermediateBoundingObject
{
public:
	IntermediateBoundingObject(void);

	void										setBoundingObjectType(bxgi::EIntermediateBoundingObjectType EIntermediateBoundingObjectTypeValue) { m_uiBoundingObjectType = EIntermediateBoundingObjectTypeValue; }
	bxgi::EIntermediateBoundingObjectType		getBoundingObjectType(void) { return m_uiBoundingObjectType; }

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
	bxgi::EIntermediateBoundingObjectType		m_uiBoundingObjectType;
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