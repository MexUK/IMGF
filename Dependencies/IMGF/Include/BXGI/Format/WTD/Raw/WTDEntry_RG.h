#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::RG_WTDEntry
{
	uint32					m_uiVTable2;
	uint32					m_uiBlockMapOffset2;
	uint32					m_uiUnknown4;
	uint32					m_uiUnknown5;
	uint32					m_uiUnknown6;
	uint32					m_uiNameOffset;
	uint32					m_uiUnknown7;
	uint16					m_usWidth;
	uint16					m_usHeight;
	uint8					m_ucD3DFormat[4];
	uint16					m_usStrideSize;
	uint8					m_ucType;
	uint8					m_ucLevels;
	float32					m_fUnknown8;
	float32					m_fUnknown9;
	float32					m_fUnknown10;
	float32					m_fUnknown11;
	float32					m_fUnknown12;
	float32					m_fUnknown13;
	uint32					m_uiPrevTextureInfoOffset;
	uint32					m_uiNextTextureInfoOffset;
	uint32					m_uiRawDataOffset;
	uint32					m_uiUnknown14;
};
#pragma pack(pop)