#pragma once

#include "nsbxcf.h"
#include <string>

class NetworkDevice;

class bxcf::LinkLayer
{
public:
	static std::string				createPacket(void);

	static NetworkDevice*			getDevice(void);
};