#pragma once

#include "nsimgf.h"
#include <string>

class imgf::DumpManager
{
public:
	void			process(void);

private:
	std::string		getEncoderClassIdFromImageExtension(std::string strFileExtension);
};