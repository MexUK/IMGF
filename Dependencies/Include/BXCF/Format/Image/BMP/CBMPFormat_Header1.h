#ifndef CBMPFormat_Header1_H
#define CBMPFormat_Header1_H

#include "bxcf.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxcf::CBMPFormat_Header1
{
	uint32						m_uiFileSize;
	uint32						m_usReserved1;
	uint16						m_usReserved2;
	uint16						m_uiBitmapOffset;
	uint32						m_uiBitmpapHeaderSize;
};
#pragma pack(pop)

#endif