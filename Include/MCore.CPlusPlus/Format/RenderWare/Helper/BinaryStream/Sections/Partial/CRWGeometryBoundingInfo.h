#ifndef CRWGeometryBoundingInfo_H
#define CRWGeometryBoundingInfo_H

#include "mcore.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3D.h"

class mcore::CRWGeometryBoundingInfo
{
public:
	CRWGeometryBoundingInfo(void) :
		m_vecCenter{ 0.0f, 0.0f, 0.0f },
		m_fCenterRadius(0.0f),
		m_bHasPosition(false),
		m_bHasNormals(false)
	{};

	void							setCenter(mcore::CVector3D& vecCenter) { m_vecCenter = vecCenter; }
	mcore::CVector3D&						getCenter(void) { return m_vecCenter; }

	void							setCenterRadius(float32 fCenterRadius) { m_fCenterRadius = fCenterRadius; }
	float32							getCenterRadius(void) { return m_fCenterRadius; }

	void							setHasPosition(bool bHasPosition) { m_bHasPosition = bHasPosition; }
	bool							doesHavePosition(void) { return m_bHasPosition; }

	void							setHasNormals(bool bHasNormals) { m_bHasNormals = bHasNormals; }
	bool							doesHaveNormals(void) { return m_bHasNormals; }

private:
	mcore::CVector3D						m_vecCenter;
	float32							m_fCenterRadius;
	bool							m_bHasPosition;
	bool							m_bHasNormals;
};

#endif