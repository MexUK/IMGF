#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/JSONContainer.h"
#include "Format/Network/JSON/JSONString.h"
#include "Format/Network/JSON/JSONValue.h"

class bxcf::JSONArray : public bxcf::JSONContainer
{
public:
	JSONArray(void) { m_uiType = JSON_ARRAY; }

	void											addValue(bxcf::JSONString *pNull, bxcf::JSONValue *pValue)
	{
		m_vecValues.push_back(pValue);

		if (pValue->m_uiType == JSON_ARRAY || pValue->m_uiType == JSON_OBJECT)
		{
			static_cast<bxcf::JSONContainer*>(pValue)->m_pParentContainer = this;
		}
	}

	void											removeValues(void)
	{
		for (auto pValue : m_vecValues)
		{
			if (pValue->m_uiType == JSON_ARRAY || pValue->m_uiType == JSON_OBJECT)
			{
				pValue->removeValues();
			}
			delete pValue;
		}
	}

	std::vector<bxcf::JSONValue*>						m_vecValues;
};