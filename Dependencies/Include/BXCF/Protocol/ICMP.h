#pragma once

#include "nsbxcf.h"
#include <string>

class bxcf::ICMP
{
public:
	static std::string		ping(std::string& strIP, std::string& strPayload, uint8 uiCode = 0, uint16 uiIdentifier = 0, uint16 uiSequenceNumber = 0, uint32 uiMTU = 1280);

	static std::string		send(std::string& strIP, uint8 uiType, uint8 uiCode, bxcf::CDataWriter& w);
	static std::string		send(std::string& strIP, uint8 uiType, uint8 uiCode, std::string& strData);

	static void				applyChecksum(CDataWriter& w);
};