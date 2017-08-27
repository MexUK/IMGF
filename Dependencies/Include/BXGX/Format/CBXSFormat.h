#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Styles/CStyleManager.h"
#include <string>
#include <unordered_map>

class bxgx::CBXSFormat
{
public:
	void			unserialize(std::string& strData, container6d_1 &umapCustomStyleGroups, container6d_1 &umapControlStyleGroups);
	void			serialize(void);
};