#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/JSONValue.h"

class bxcf::JSONString : public bxcf::JSONValue
{
public:
	JSONString(void) { m_uiType = JSON_STRING; }
	std::string										m_strValue;
};