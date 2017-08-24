#ifndef CIMGFormat_VersionFastman92_Header2_H
#define CIMGFormat_VersionFastman92_Header2_H

#include "bxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::CIMGFormat_VersionFastman92_Header2
{
	uint32		m_uiCheck;
	uint32		m_uiEntryCount;
	uint8		m_strReserved1[8];
};
#pragma pack(pop)

#endif