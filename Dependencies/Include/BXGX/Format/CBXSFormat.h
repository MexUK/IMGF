#pragma once

#include <string>

class CBXSFormat
{
public:
	void			unserialize(std::string strFilePath, bool bFileIsDefaultStyles);
	void			serialize(void);
};