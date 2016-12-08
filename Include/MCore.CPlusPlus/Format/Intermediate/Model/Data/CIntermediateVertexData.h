#ifndef CIntermediateVertexData_H
#define CIntermediateVertexData_H

#include "mcore.h"
#include "Type/Types.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"

class mcore::CIntermediateVertexData
{
public:
	CIntermediateVertexData(void) :
		m_uiColour(0)
	{
		m_vecPosition.m_x = 0.0f;
		m_vecPosition.m_y = 0.0f;
		m_vecPosition.m_z = 0.0f;
		m_vecNormal.m_x = 0.0f;
		m_vecNormal.m_y = 0.0f;
		m_vecNormal.m_z = 0.0f;
		m_vecTextureCoordinates.m_x = 0.0f;
		m_vecTextureCoordinates.m_y = 0.0f;
		m_vecNormal2.m_x = 0.0f;
		m_vecNormal2.m_y = 0.0f;
		m_vecNormal2.m_z = 0.0f;
		m_vecNormal2.m_w = 0.0f;
	};

	void								setPosition(mcore::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	mcore::CVector3D&							getPosition(void) { return m_vecPosition; }

	void								setNormal(mcore::CVector3D& vecNormal) { m_vecNormal = vecNormal; }
	mcore::CVector3D&							getNormal(void) { return m_vecNormal; }

	void								setColour(uint32 uiColour) { m_uiColour = uiColour; }
	uint32								getColour(void) { return m_uiColour; }

	void								setTextureCoordinates(mcore::CVector2D& vecTextureCoordinates) { m_vecTextureCoordinates = vecTextureCoordinates; }
	mcore::CVector2D&							getTextureCoordinates(void) { return m_vecTextureCoordinates; }

	void								setNormal2(mcore::CVector4D& vecNormal2) { m_vecNormal2 = vecNormal2; }
	mcore::CVector4D&							getNormal2(void) { return m_vecNormal2; }

private:
	mcore::CVector3D							m_vecPosition;
	mcore::CVector3D							m_vecNormal;
	uint32								m_uiColour; // RGBA
	mcore::CVector2D							m_vecTextureCoordinates;
	mcore::CVector4D							m_vecNormal2;
};

#endif