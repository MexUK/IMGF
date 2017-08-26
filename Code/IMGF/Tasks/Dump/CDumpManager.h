#pragma once

#include <string>

class CDumpManager
{
public:
	void			process(void);

private:
	std::string		getEncoderClassIdFromImageExtension(std::string strFileExtension);
};