#ifndef CIntermediateIndexData_H
#define CIntermediateIndexData_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3u.h"

class bxcf::CIntermediateIndexData
{
public:
	CIntermediateIndexData(void)
	{
		m_vecVertexIndices.x = 0;
		m_vecVertexIndices.y = 0;
		m_vecVertexIndices.z = 0;
	};

	void								setVertexIndices(bxcf::Vec3u& vecVertexIndices) { m_vecVertexIndices = vecVertexIndices; }
	bxcf::Vec3u&						getVertexIndices(void) { return m_vecVertexIndices; }

private:
	bxcf::Vec3u						m_vecVertexIndices;
};

#endif