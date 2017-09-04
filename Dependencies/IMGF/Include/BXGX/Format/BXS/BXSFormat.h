#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Style/StyleManager.h"
#include <string>
#include <unordered_map>

class bxgx::BXSFormat
{
public:
	void			unserialize(std::string& strData, container6d_1 &umapCustomStyleGroups, container6d_1 &umapControlStyleGroups);
	void			serialize(void);
};