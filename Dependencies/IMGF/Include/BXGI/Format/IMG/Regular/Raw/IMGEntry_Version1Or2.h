#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::RG_IMGEntry_Version1Or2
{
	uint32			m_uiOffsetInSectors;
	uint32			m_uiSizeInSectors;
	uint8			m_szName[24];
};
#pragma pack(pop)