#ifndef CIMGFormat_Version3_Header1_H
#define CIMGFormat_Version3_Header1_H

#include "bxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::RG_CIMGFormat_Version3_Header1
{
	uint32			m_uiIdentifier;
	uint32			m_uiVersion;
	uint32			m_uiEntryCount;
	uint32			m_uiTableSize;
	uint16			m_usTableItemsSize;
	uint16			m_usUnknown;
};
#pragma pack(pop)

#endif