#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/JSONValue.h"

class bxcf::JSONBoolean : public bxcf::JSONValue
{
public:
	JSONBoolean(void) { m_uiType = JSON_BOOLEAN; }
	bool											m_bValue;
};