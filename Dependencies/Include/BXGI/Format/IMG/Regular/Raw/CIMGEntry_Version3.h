#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::RG_CIMGEntry_Version3
{
	uint32			m_uiItemSize;
	uint32			m_uiRageResourceTypeIdentifier;
	uint32			m_uiOffsetInSectors;
	uint16			m_usSizeInSectors;
	uint16			m_usFlags;
};
#pragma pack(pop)