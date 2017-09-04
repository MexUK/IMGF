#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::RG_IMGFormat_Version2_Header1
{
	uint8			m_ucMagicNumber[4];
	uint32			m_uiEntryCount;
};
#pragma pack(pop)