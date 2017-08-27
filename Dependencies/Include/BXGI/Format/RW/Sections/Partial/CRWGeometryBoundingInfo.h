#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3f.h"

class bxgi::CRWGeometryBoundingInfo
{
public:
	CRWGeometryBoundingInfo(void);

	void							setCenter(bxcf::Vec3f& vecCenter) { m_vecCenter = vecCenter; }
	bxcf::Vec3f&						getCenter(void) { return m_vecCenter; }

	void							setCenterRadius(float32 fCenterRadius) { m_fCenterRadius = fCenterRadius; }
	float32							getCenterRadius(void) { return m_fCenterRadius; }

	void							setHasPosition(bool bHasPosition) { m_bHasPosition = bHasPosition; }
	bool							doesHavePosition(void) { return m_bHasPosition; }

	void							setHasNormals(bool bHasNormals) { m_bHasNormals = bHasNormals; }
	bool							doesHaveNormals(void) { return m_bHasNormals; }

private:
	bxcf::Vec3f						m_vecCenter;
	float32							m_fCenterRadius;
	bool							m_bHasPosition;
	bool							m_bHasNormals;
};