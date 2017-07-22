#ifndef CWDRBlock_VertexData_H
#define CWDRBlock_VertexData_H

#include "bxa.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"

class bxa::CWDRBlock_VertexData
{
public:
	bxa::CVector3D					m_vecPosition;
	bxa::CVector3D					m_vecNormals;
	uint32						m_uiColour; // RGBA
	bxa::CVector2D					m_vecTextureCoordinates;
	float32						m_fNormals2[4];
};

#endif