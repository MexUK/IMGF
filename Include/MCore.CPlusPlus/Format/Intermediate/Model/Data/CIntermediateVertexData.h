#ifndef CIntermediateVertexData_H
#define CIntermediateVertexData_H

#include "bxa.h"
#include "Type/Types.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"

class bxa::CIntermediateVertexData
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

	void								setPosition(bxa::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxa::CVector3D&							getPosition(void) { return m_vecPosition; }

	void								setNormal(bxa::CVector3D& vecNormal) { m_vecNormal = vecNormal; }
	bxa::CVector3D&							getNormal(void) { return m_vecNormal; }

	void								setColour(uint32 uiColour) { m_uiColour = uiColour; }
	uint32								getColour(void) { return m_uiColour; }

	void								setTextureCoordinates(bxa::CVector2D& vecTextureCoordinates) { m_vecTextureCoordinates = vecTextureCoordinates; }
	bxa::CVector2D&							getTextureCoordinates(void) { return m_vecTextureCoordinates; }

	void								setNormal2(bxa::CVector4D& vecNormal2) { m_vecNormal2 = vecNormal2; }
	bxa::CVector4D&							getNormal2(void) { return m_vecNormal2; }

private:
	bxa::CVector3D							m_vecPosition;
	bxa::CVector3D							m_vecNormal;
	uint32								m_uiColour; // RGBA
	bxa::CVector2D							m_vecTextureCoordinates;
	bxa::CVector4D							m_vecNormal2;
};

#endif