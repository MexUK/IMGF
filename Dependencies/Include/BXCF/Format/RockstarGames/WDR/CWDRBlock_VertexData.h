#ifndef CWDRBlock_VertexData_H
#define CWDRBlock_VertexData_H

#include "bxcf.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"

class bxcf::CWDRBlock_VertexData
{
public:
	bxcf::CVector3D					m_vecPosition;
	bxcf::CVector3D					m_vecNormals;
	uint32						m_uiColour; // RGBA
	bxcf::CVector2D					m_vecTextureCoordinates;
	float32						m_fNormals2[4];
};

#endif