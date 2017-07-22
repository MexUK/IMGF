#ifndef CJSONManager_H
#define CJSONManager_H

#include "bxa.h"
#include <vector>
#include <unordered_map>

// todo - move classes and enums to separate header files

enum bxa::eJsonTypes : unsigned char
{
	JSON_STRING,
	JSON_NUMBER,
	JSON_BOOLEAN,
	JSON_NULL,
	JSON_ARRAY,
	JSON_OBJECT
};

class bxa::CJSONString;
class bxa::CJSONValue;

class bxa::CJSONValue
{
public:
	virtual void									addValue(bxa::CJSONString *pKey, bxa::CJSONValue *pValue) {};
	virtual void									removeValues(void) {};

	bxa::eJsonTypes										m_eType;
};

class bxa::CJSONString : public bxa::CJSONValue
{
public:
	CJSONString(void) { m_eType = JSON_STRING; }
	std::string										m_strValue;
};

class bxa::CJSONNumber : public bxa::CJSONValue
{
public:
	CJSONNumber(void) { m_eType = JSON_NUMBER; }
	double											m_dValue;
};

class bxa::CJSONBoolean : public bxa::CJSONValue
{
public:
	CJSONBoolean(void) { m_eType = JSON_BOOLEAN; }
	bool											m_bValue;
};

class bxa::CJSONNull : public bxa::CJSONValue
{
public:
	CJSONNull(void) { m_eType = JSON_NULL; }
};

class bxa::CJSONContainer : public bxa::CJSONValue
{
public:
	bxa::CJSONContainer*									m_pParentContainer;
};

class bxa::CJSONArray : public bxa::CJSONContainer
{
public:
	CJSONArray(void) { m_eType = JSON_ARRAY; }

	void											addValue(bxa::CJSONString *pNull, bxa::CJSONValue *pValue)
	{
		m_vecValues.push_back(pValue);

		if (pValue->m_eType == JSON_ARRAY || pValue->m_eType == JSON_OBJECT)
		{
			static_cast<bxa::CJSONContainer*>(pValue)->m_pParentContainer = this;
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

	std::vector<bxa::CJSONValue*>						m_vecValues;
};

class bxa::CJSONObject : public bxa::CJSONContainer
{
public:
	CJSONObject(void) { m_eType = JSON_OBJECT; }

	void											addValue(bxa::CJSONString *pKey, bxa::CJSONValue *pValue)
	{
		m_umapValues[pKey] = pValue;

		if (pValue->m_eType == JSON_ARRAY || pValue->m_eType == JSON_OBJECT)
		{
			static_cast<bxa::CJSONContainer*>(pValue)->m_pParentContainer = this;
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

	std::unordered_map<bxa::CJSONString*, bxa::CJSONValue*>	m_umapValues;
};

class bxa::CJSONManager
{
public:
	CJSONManager(void);

	bxa::CJSONObject*				unserializeString(std::string strJSON);

	//void						loadObjectIntoLua(CJSONObject *pObject);

private:
	std::string					parseString(std::string& strJSON);
	double						parseNumber(std::string& strJSON);

	void						setLatestKey(bxa::CJSONString *pString) { m_pLatestKey = pString; }
	bxa::CJSONString*				getLatestKey(void) { return m_pLatestKey; }

	//void						loadArrayIntoLua(CJSONArray *pArray);
	//void						loadValueIntoLua(CJSONValue *pValue);

	bxa::CJSONObject*				m_pEntryContainer;
	bxa::CJSONContainer*				m_pLatestContainer;
	bool						m_bExpectingKeyOrObjectEnd;
	bxa::CJSONString*				m_pLatestKey;
	unsigned long				m_uiSeek;
};

#endif