#pragma once

#include "nsbxgi.h"
#include <string>

struct bxgi::DATEntry_Paths_Fastman92_Header
{
	uint32			m_uiFourCC; // 0xFFFFFFFF
	std::string		m_strFormat; // FM92
	uint8			m_ucNicknameLength;
	std::string		m_strNickname; // char					m_szNickname[m_ucNicknameLength];
	std::string		m_strFormatVersion;
	uint32			m_uiPathNodeCount;
	uint32			m_uiVehicleNodeCount;
	uint32			m_uiPedNodeCount;
	uint32			m_uiNaviNodeCount;
	uint32			m_uiLinkCount;
};