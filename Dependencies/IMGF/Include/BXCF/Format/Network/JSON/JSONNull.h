#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/JSONValue.h"

class bxcf::JSONNull : public bxcf::JSONValue
{
public:
	JSONNull(void) { m_uiType = JSON_NULL; }
};