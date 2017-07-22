#pragma once

#include "BXA.h"
#include "Stream/CDataWriter.h"
#include <string>

class NetworkDevice;

class bxa::LinkLayer
{
public:
	static std::string				createPacket(void);

	static NetworkDevice*			getDevice(void);
};