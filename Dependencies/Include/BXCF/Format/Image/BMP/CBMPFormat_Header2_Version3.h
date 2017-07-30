#ifndef CBMPFormat_Header2_Version3_H
#define CBMPFormat_Header2_Version3_H

#include "bxcf.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxcf::CBMPFormat_Header2_Version3
{
	uint32						m_uiWidth;
	uint32						m_uiHeight;
	uint16						m_usPlaneCount;
	uint16						m_usBPP; // if < 16 then has palette
	uint32						m_uiCompressionMethods;
	uint32						m_uiBitmapSize;
	uint32						m_uiHorizontalResolution;
	uint32						m_uiVerticalResolution;
	uint32						m_uiColoursUsed;
	uint32						m_uiColoursImportant;
};
#pragma pack(pop)

#endif