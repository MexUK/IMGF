#pragma once

#include "Type/Types.h"
#include "Styles/CStyleManager.h"
#include <string>
#include <unordered_map>

class CBXSFormat
{
public:
	void			unserialize(std::string strFilePath, container6d_1 &umapCustomStyleGroups, container6d_1 &umapControlStyleGroups);
	void			serialize(void);
};