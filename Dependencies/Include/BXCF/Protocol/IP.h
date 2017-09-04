#pragma once

#include "nsbxcf.h"
#include "Stream/DataWriter.h"

class bxcf::IP
{
public:
	static void						send(std::string& strIP, DataWriter& w);

	static std::string				createPacketIncludingLinkLayer(void);
	static std::string				createPacket(void);

	static uint16					getInternetChecksum(std::string& strData);
};