#pragma once

#include "nsbxcf.h"
#include <vector>
#include <unordered_map>

class bxcf::JSONObject;
class bxcf::JSONContainer;
class bxcf::JSONString;

class bxcf::JSONManager
{
public:
	JSONManager(void);

	bxcf::JSONObject*			unserializeString(std::string strJSON);

	//void						loadObjectIntoLua(JSONObject *pObject);

private:
	std::string					parseString(std::string& strJSON);
	float64						parseNumber(std::string& strJSON);

	void						setLatestKey(bxcf::JSONString *pString) { m_pLatestKey = pString; }
	bxcf::JSONString*			getLatestKey(void) { return m_pLatestKey; }

	//void						loadArrayIntoLua(JSONArray *pArray);
	//void						loadValueIntoLua(JSONValue *pValue);

	bxcf::JSONObject*			m_pEntryContainer;
	bxcf::JSONContainer*		m_pLatestContainer;
	bool						m_bExpectingKeyOrObjectEnd;
	bxcf::JSONString*			m_pLatestKey;
	uint32						m_uiSeek;
};