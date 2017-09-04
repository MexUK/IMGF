#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/JSONContainer.h"
#include "Format/Network/JSON/JSONString.h"
#include "Format/Network/JSON/JSONValue.h"

class bxcf::JSONObject : public bxcf::JSONContainer
{
public:
	JSONObject(void) { m_uiType = JSON_OBJECT; }

	void											addValue(bxcf::JSONString *pKey, bxcf::JSONValue *pValue)
	{
		m_umapValues[pKey] = pValue;

		if (pValue->m_uiType == JSON_ARRAY || pValue->m_uiType == JSON_OBJECT)
		{
			static_cast<bxcf::JSONContainer*>(pValue)->m_pParentContainer = this;
		}
	}

	void											removeValues(void)
	{
		for (auto it : m_umapValues)
		{
			delete it.first;
			if (it.second->m_uiType == JSON_ARRAY || it.second->m_uiType == JSON_OBJECT)
			{
				it.second->removeValues();
			}
			delete it.second;
		}
	}

	std::unordered_map<bxcf::JSONString*, bxcf::JSONValue*>	m_umapValues;
};