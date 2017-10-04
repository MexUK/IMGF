#pragma once

#include "nsimgf.h"
#include <string>

class imgf::DumpManager
{
public:
	bool			process(void);

private:
	std::string		getEncoderClassIdFromImageExtension(std::string strFileExtension);
};