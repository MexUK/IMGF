#ifndef CIMGEntry_Fastman92_H
#define CIMGEntry_Fastman92_H

#include "bxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::CIMGEntry_Fastman92
{
	uint32		m_uiOffsetInSectors;
	uint32		m_uiUncompressedSizeInSectors;
	uint16		m_usPaddedBytesCountInAlignedOriginalSize;
	uint32		m_uiSizeInSectors;
	uint16		m_usPaddedBytesCountInAlignedPackedSize;
	uint32		m_uiCompressionAlgorithmId	: 4; // eIMGVersionFastman92CompressionAlgorithm
	uint32		m_uiEncryptionAlgorithmId	: 4;
	uint32		m_uiPad1					: 24;
	uint8		m_strName[40];
	uint8		m_strPad2[8];
};
#pragma pack(pop)

#endif