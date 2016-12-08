#ifndef CDDSFormat_Header_DDS_HEADER_DXT10_H
#define CDDSFormat_Header_DDS_HEADER_DXT10_H

#include "mcore.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct mcore::CDDSFormat_Header_DDS_HEADER_DXT10
{
	uint32					m_uiDXGIFormat;
	uint32					m_uiD3D10ResourceDimension; // D3D10_RESOURCE_DIMENSION - assume 4 bytes
	int32					m_iMiscFlag;
	int32					m_iArraySize;
	int32					m_iMiscFlag2;
};
#pragma pack(pop)

#endif