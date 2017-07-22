#ifndef CBMPFormat_Header2_Version2_H
#define CBMPFormat_Header2_Version2_H

#include "bxa.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxa::CBMPFormat_Header2_Version2
{
	uint32						m_uiWidth;
	uint32						m_uiHeight;
	uint16						m_usPlaneCount;
	uint16						m_usBPP; // if < 16 then has palette
};
#pragma pack(pop)

#endif