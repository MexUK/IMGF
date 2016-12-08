#ifndef CDDSFormat_Header_DDS_PIXELFORMAT_Part2_H
#define CDDSFormat_Header_DDS_PIXELFORMAT_Part2_H

#include "mcore.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct mcore::CDDSFormat_Header_DDS_PIXELFORMAT_Part2
{
	uint32					m_uiCaps;
	uint32					m_uiCaps2;
	uint32					m_uiCaps3;
	uint32					m_uiCaps4;
	uint32					m_uiReserved2;
};
#pragma pack(pop)

#endif