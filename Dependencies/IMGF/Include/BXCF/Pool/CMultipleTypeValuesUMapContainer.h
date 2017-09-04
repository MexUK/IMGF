#ifndef CMultipleTypeValuesUMapContainer_H
#define CMultipleTypeValuesUMapContainer_H

#include "bxcf.h"
#include "Type/Types.h"
#include <unordered_map>

template <class KeyClass>
class bxcf::CMultipleTypeValuesUMapContainer // todo - use either Pool or Container for this class and vectorpool class
{
public:
	void									setEntry(KeyClass key, bool bValue);
	void									setEntry(KeyClass key, uint32 uiValue);
	void									setEntry(KeyClass key, int32 iValue);
	void									setEntry(KeyClass key, float32 fValue);
	void									setEntry(KeyClass key, std::string strValue);
	template <typename ValueType>
	void									setEntry(KeyClass key, ValueType value);			// does copy the value
	template <typename ValueType>
	void									setEntryPointer(KeyClass key, ValueType *pValue);	// does not copy the value
	void									setEntryVoidPointer(KeyClass key, void *pValue);	// does not copy the value
	bool									doesEntryExist(KeyClass key);
	bool									isEmpty(void);
	uint32									getEntryCount(void);
	std::unordered_map<KeyClass, void*>&	getEntries(void) { return m_umapEntries; }
	template <typename ValueType>
	ValueType								getEntry(KeyClass key);						// doesn't check if the key exists
	template <typename ValueType>
	ValueType*								getEntryPointer(KeyClass key);				// does check if the key exists
	void*									getEntryVoidPointer(KeyClass key);			// does check if the key exists
	void									removeAllEntries(void);
	void									removeAllEntriesNoDelete(void);
	void									removeEntry(KeyClass key);

protected:
	std::unordered_map<KeyClass, void*>		m_umapEntries;
};




template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntry(KeyClass key, bool bValue)
{
	setEntry<bool>(key, bValue);
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntry(KeyClass key, uint32 uiValue)
{
	setEntry<uint32>(key, uiValue);
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntry(KeyClass key, int32 iValue)
{
	setEntry<int32>(key, iValue);
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntry(KeyClass key, float32 fValue)
{
	setEntry<float32>(key, fValue);
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntry(KeyClass key, std::string strValue)
{
	setEntry<std::string>(key, strValue);
}

template <class KeyClass>
template <typename ValueType>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntry(KeyClass key, ValueType value)
{
	setEntryPointer(key, new ValueType(value));
}

template <class KeyClass>
template <typename ValueType>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntryPointer(KeyClass key, ValueType *pValue)
{
	m_umapEntries[key] = pValue;
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::setEntryVoidPointer(KeyClass key, void *pValue)
{
	m_umapEntries[key] = pValue;
}

template <class KeyClass>
bool				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::doesEntryExist(KeyClass key)
{
	return m_umapEntries.count(key) == 1;
}

template <class KeyClass>
bool				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::isEmpty(void)
{
	return m_umapEntries.empty();
}

template <class KeyClass>
uint32				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::getEntryCount(void)
{
	return m_umapEntries.size();
}

template <class KeyClass>
template <typename ValueType>
ValueType			bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::getEntry(KeyClass key)
{
	return *((ValueType*) m_umapEntries[key]);
}

template <class KeyClass>
template <typename ValueType>
ValueType*			bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::getEntryPointer(KeyClass key)
{
	if (!doesEntryExist(key))
	{
		return nullptr;
	}
	return (ValueType*) m_umapEntries[key];
}

template <class KeyClass>
void*				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::getEntryVoidPointer(KeyClass key)
{
	if (!doesEntryExist(key))
	{
		return nullptr;
	}
	return m_umapEntries[key];
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::removeAllEntries(void)
{
	for (std::pair<KeyClass, void*> it : m_umapEntries)
	{
		delete m_umapEntries[it.first];
	}
	m_umapEntries.clear();
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::removeAllEntriesNoDelete(void)
{
	m_umapEntries.clear();
}

template <class KeyClass>
void				bxcf::CMultipleTypeValuesUMapContainer<KeyClass>::removeEntry(KeyClass key)
{
	delete m_umapEntries[key];
	m_umapEntries.erase(key);
}

#endif