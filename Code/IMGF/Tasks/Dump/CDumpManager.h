#pragma once

#include "nsimgf.h"
#include <string>

class imgf::CDumpManager
{
public:
	void			process(void);

private:
	std::string		getEncoderClassIdFromImageExtension(std::string strFileExtension);
};