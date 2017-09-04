#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/EJSONType.h"

class bxcf::JSONString;
class bxcf::JSONValue;

class bxcf::JSONValue
{
public:
	virtual void									addValue(bxcf::JSONString *pKey, bxcf::JSONValue *pValue) {}
	virtual void									removeValues(void) {}

	bxcf::EJSONType									m_uiType;
};