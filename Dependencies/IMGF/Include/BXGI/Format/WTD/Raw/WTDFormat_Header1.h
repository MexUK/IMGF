#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::RG_WTDFormat_Header1
{
	uint32					m_uiMagicNumber;
	uint32					m_uiType;
	uint32					m_uiFlags;
};
#pragma pack(pop)