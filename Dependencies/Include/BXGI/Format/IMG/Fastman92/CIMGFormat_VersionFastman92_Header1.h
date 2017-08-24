#ifndef CIMGFormat_VersionFastman92_Header1_H
#define CIMGFormat_VersionFastman92_Header1_H

#include "bxgi.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxgi::CIMGFormat_VersionFastman92_Header1
{
	uint8		m_ucIMGVersion[4];
	uint32		m_uiFastman92IMGVersion		: 4;
	uint32		m_uiEncryptionAlgorithmId	: 4;
	uint32		m_uiGameId					: 1;
	uint32		m_uiPad						: 23;
	uint8		m_strAuthorName[12];
};
#pragma pack(pop)

#endif