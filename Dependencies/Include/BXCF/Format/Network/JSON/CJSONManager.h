#pragma once

#include "nsbxcf.h"
#include <vector>
#include <unordered_map>

// todo - move classes and enums to separate header files

enum bxcf::EJsonType : unsigned char
{
	JSON_STRING,
	JSON_NUMBER,
	JSON_BOOLEAN,
	JSON_NULL,
	JSON_ARRAY,
	JSON_OBJECT
};

class bxcf::CJSONString;
class bxcf::CJSONValue;

class bxcf::CJSONValue
{
public:
	virtual void									addValue(bxcf::CJSONString *pKey, bxcf::CJSONValue *pValue) {}
	virtual void									removeValues(void) {}

	bxcf::EJsonType										m_eType;
};

class bxcf::CJSONString : public bxcf::CJSONValue
{
public:
	CJSONString(void) { m_eType = JSON_STRING; }
	std::string										m_strValue;
};

class bxcf::CJSONNumber : public bxcf::CJSONValue
{
public:
	CJSONNumber(void) { m_eType = JSON_NUMBER; }
	double											m_dValue;
};

class bxcf::CJSONBoolean : public bxcf::CJSONValue
{
public:
	CJSONBoolean(void) { m_eType = JSON_BOOLEAN; }
	bool											m_bValue;
};

class bxcf::CJSONNull : public bxcf::CJSONValue
{
public:
	CJSONNull(void) { m_eType = JSON_NULL; }
};

class bxcf::CJSONContainer : public bxcf::CJSONValue
{
public:
	bxcf::CJSONContainer*									m_pParentContainer;
};

class bxcf::CJSONArray : public bxcf::CJSONContainer
{
public:
	CJSONArray(void) { m_eType = JSON_ARRAY; }

	void											addValue(bxcf::CJSONString *pNull, bxcf::CJSONValue *pValue)
	{
		m_vecValues.push_back(pValue);

		if (pValue->m_eType == JSON_ARRAY || pValue->m_eType == JSON_OBJECT)
		{
			static_cast<bxcf::CJSONContainer*>(pValue)->m_pParentContainer = this;
		}
	}

	void											removeValues(void)
	{
		for (auto pValue : m_vecValues)
		{
			if (pValue->m_eType == JSON_ARRAY || pValue->m_eType == JSON_OBJECT)
			{
				pValue->removeValues();
			}
			delete pValue;
		}
	}

	std::vector<bxcf::CJSONValue*>						m_vecValues;
};

class bxcf::CJSONObject : public bxcf::CJSONContainer
{
public:
	CJSONObject(void) { m_eType = JSON_OBJECT; }

	void											addValue(bxcf::CJSONString *pKey, bxcf::CJSONValue *pValue)
	{
		m_umapValues[pKey] = pValue;

		if (pValue->m_eType == JSON_ARRAY || pValue->m_eType == JSON_OBJECT)
		{
			static_cast<bxcf::CJSONContainer*>(pValue)->m_pParentContainer = this;
		}
	}

	void											removeValues(void)
	{
		for (auto it : m_umapValues)
		{
			delete it.first;
			if (it.second->m_eType == JSON_ARRAY || it.second->m_eType == JSON_OBJECT)
			{
				it.second->removeValues();
			}
			delete it.second;
		}
	}

	std::unordered_map<bxcf::CJSONString*, bxcf::CJSONValue*>	m_umapValues;
};

class bxcf::CJSONManager
{
public:
	CJSONManager(void);

	bxcf::CJSONObject*				unserializeString(std::string strJSON);

	//void						loadObjectIntoLua(CJSONObject *pObject);

private:
	std::string					parseString(std::string& strJSON);
	double						parseNumber(std::string& strJSON);

	void						setLatestKey(bxcf::CJSONString *pString) { m_pLatestKey = pString; }
	bxcf::CJSONString*				getLatestKey(void) { return m_pLatestKey; }

	//void						loadArrayIntoLua(CJSONArray *pArray);
	//void						loadValueIntoLua(CJSONValue *pValue);

	bxcf::CJSONObject*				m_pEntryContainer;
	bxcf::CJSONContainer*				m_pLatestContainer;
	bool						m_bExpectingKeyOrObjectEnd;
	bxcf::CJSONString*				m_pLatestKey;
	unsigned long				m_uiSeek;
};