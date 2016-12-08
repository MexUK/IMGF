#ifndef CWDRBlock_VertexData_H
#define CWDRBlock_VertexData_H

#include "mcore.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"

class mcore::CWDRBlock_VertexData
{
public:
	mcore::CVector3D					m_vecPosition;
	mcore::CVector3D					m_vecNormals;
	uint32						m_uiColour; // RGBA
	mcore::CVector2D					m_vecTextureCoordinates;
	float32						m_fNormals2[4];
};

#endif