#ifndef CIntermediateIndexData_H
#define CIntermediateIndexData_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3ui32.h"

class bxcf::CIntermediateIndexData
{
public:
	CIntermediateIndexData(void)
	{
		m_vecVertexIndices.m_x = 0;
		m_vecVertexIndices.m_y = 0;
		m_vecVertexIndices.m_z = 0;
	};

	void								setVertexIndices(bxcf::CVector3ui32& vecVertexIndices) { m_vecVertexIndices = vecVertexIndices; }
	bxcf::CVector3ui32&						getVertexIndices(void) { return m_vecVertexIndices; }

private:
	bxcf::CVector3ui32						m_vecVertexIndices;
};

#endif