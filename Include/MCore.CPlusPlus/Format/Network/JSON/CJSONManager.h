#ifndef CJSONManager_H
#define CJSONManager_H

#include "mcore.h"
#include <vector>
#include <unordered_map>

// todo - move classes and enums to separate header files

enum mcore::eJsonTypes : unsigned char
{
	JSON_STRING,
	JSON_NUMBER,
	JSON_BOOLEAN,
	JSON_NULL,
	JSON_ARRAY,
	JSON_OBJECT
};

class mcore::CJSONString;
class mcore::CJSONValue;

class mcore::CJSONValue
{
public:
	virtual void									addValue(mcore::CJSONString *pKey, mcore::CJSONValue *pValue) {};
	virtual void									removeValues(void) {};

	mcore::eJsonTypes										m_eType;
};

class mcore::CJSONString : public mcore::CJSONValue
{
public:
	CJSONString(void) { m_eType = JSON_STRING; }
	std::string										m_strValue;
};

class mcore::CJSONNumber : public mcore::CJSONValue
{
public:
	CJSONNumber(void) { m_eType = JSON_NUMBER; }
	double											m_dValue;
};

class mcore::CJSONBoolean : public mcore::CJSONValue
{
public:
	CJSONBoolean(void) { m_eType = JSON_BOOLEAN; }
	bool											m_bValue;
};

class mcore::CJSONNull : public mcore::CJSONValue
{
public:
	CJSONNull(void) { m_eType = JSON_NULL; }
};

class mcore::CJSONContainer : public mcore::CJSONValue
{
public:
	mcore::CJSONContainer*									m_pParentContainer;
};

class mcore::CJSONArray : public mcore::CJSONContainer
{
public:
	CJSONArray(void) { m_eType = JSON_ARRAY; }

	void											addValue(mcore::CJSONString *pNull, mcore::CJSONValue *pValue)
	{
		m_vecValues.push_back(pValue);

		if (pValue->m_eType == JSON_ARRAY || pValue->m_eType == JSON_OBJECT)
		{
			static_cast<mcore::CJSONContainer*>(pValue)->m_pParentContainer = this;
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

	std::vector<mcore::CJSONValue*>						m_vecValues;
};

class mcore::CJSONObject : public mcore::CJSONContainer
{
public:
	CJSONObject(void) { m_eType = JSON_OBJECT; }

	void											addValue(mcore::CJSONString *pKey, mcore::CJSONValue *pValue)
	{
		m_umapValues[pKey] = pValue;

		if (pValue->m_eType == JSON_ARRAY || pValue->m_eType == JSON_OBJECT)
		{
			static_cast<mcore::CJSONContainer*>(pValue)->m_pParentContainer = this;
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

	std::unordered_map<mcore::CJSONString*, mcore::CJSONValue*>	m_umapValues;
};

class mcore::CJSONManager
{
public:
	CJSONManager(void);

	mcore::CJSONObject*				unserializeString(std::string strJSON);

	//void						loadObjectIntoLua(CJSONObject *pObject);

private:
	std::string					parseString(std::string& strJSON);
	double						parseNumber(std::string& strJSON);

	void						setLatestKey(mcore::CJSONString *pString) { m_pLatestKey = pString; }
	mcore::CJSONString*				getLatestKey(void) { return m_pLatestKey; }

	//void						loadArrayIntoLua(CJSONArray *pArray);
	//void						loadValueIntoLua(CJSONValue *pValue);

	mcore::CJSONObject*				m_pEntryContainer;
	mcore::CJSONContainer*				m_pLatestContainer;
	bool						m_bExpectingKeyOrObjectEnd;
	mcore::CJSONString*				m_pLatestKey;
	unsigned long				m_uiSeek;
};

#endif