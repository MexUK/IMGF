#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/JSONValue.h"

class bxcf::JSONNumber : public bxcf::JSONValue
{
public:
	JSONNumber(void) { m_uiType = JSON_NUMBER; }
	double											m_dValue;
};