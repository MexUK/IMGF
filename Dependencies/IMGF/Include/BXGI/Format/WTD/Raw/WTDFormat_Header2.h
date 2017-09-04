#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::RG_WTDFormat_Header2
{
	uint32					m_uiVTable;
	uint32					m_uiBlockMapOffset;
	uint32					m_uiParentDictionary;
	uint32					m_uiUsageCount;
	uint32					m_uiHashTableOffset;
	uint16					m_usTextureCount;
	uint16					m_usUnknown1;
	uint32					m_uiTextureListOffset;
	uint16					m_usUnknown2;
	uint16					m_usUnknown3;
};
#pragma pack(pop)