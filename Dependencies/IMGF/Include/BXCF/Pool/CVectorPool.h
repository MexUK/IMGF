#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include <vector>

template <class T>
class bxcf::CVectorPool
{
public:
	bool									isEntryAtIndex(uint32 uiEntryIndex);
	uint32									getEntryCount(void);
	std::vector<T>&							getEntries(void) { return m_vecEntries; }
	T										getEntryByIndex(uint32 uiEntryIndex);
	T										getFirstEntry(void);
	T										getLastEntry(void);
	void									addEntry(T pEntry);
	void									addEntryAtPosition(T pEntry, uint32 uiPosition);
	virtual void							removeAllEntries(void);
	virtual void							removeEntry(T pEntry);
	uint32									getIndexByEntry(T pEntry);
	void									setEntryByIndex(uint32 uiEntryIndex, T pEntry);
	void									swapEntries(T pEntry1, T pEntry2);
	uint32									getNextEntryIndex(void);
	void									moveEntryToPosition(T pEntry, uint32 uiPosition);

protected:
	std::vector<T>							m_vecEntries;
};




template <class T>
bool				bxcf::CVectorPool<T>::isEntryAtIndex(uint32 uiEntryIndex)
{
	return uiEntryIndex < m_vecEntries.size();
}

template <class T>
uint32				bxcf::CVectorPool<T>::getEntryCount(void)
{
	return m_vecEntries.size();
}

template <class T>
T					bxcf::CVectorPool<T>::getEntryByIndex(uint32 uiEntryIndex)
{
	if (isEntryAtIndex(uiEntryIndex))
	{
		return m_vecEntries[uiEntryIndex];
	}
	return nullptr;
}

template <class T>
void				bxcf::CVectorPool<T>::removeAllEntries(void)
{
	for (auto pEntry : m_vecEntries)
	{
		//pEntry->unload(); // todo - use destructors, not unload()
		delete pEntry;
	}
	m_vecEntries.clear();
}

template <class T>
void				bxcf::CVectorPool<T>::addEntry(T pEntry)
{
	m_vecEntries.push_back(pEntry);
}

template <class T>
void				bxcf::CVectorPool<T>::addEntryAtPosition(T pEntry, uint32 uiPosition)
{
	m_vecEntries.insert(m_vecEntries.begin() + uiPosition, pEntry);
}

template <class T>
void				bxcf::CVectorPool<T>::removeEntry(T pEntry)
{
	std::vector<T>::iterator it = std::find(m_vecEntries.begin(), m_vecEntries.end(), pEntry);
	m_vecEntries.erase(it);
	//pEntry->unload();
	// todo - delete objects elsewhere, delete pEntry;
}

template <class T>
uint32				bxcf::CVectorPool<T>::getNextEntryIndex(void)
{
	return m_vecEntries.size();
}

template <class T>
T					bxcf::CVectorPool<T>::getFirstEntry(void)
{
	return m_vecEntries[0];
}

template <class T>
T					bxcf::CVectorPool<T>::getLastEntry(void)
{
	return m_vecEntries[m_vecEntries.size() - 1];
}

template <class T>
uint32				bxcf::CVectorPool<T>::getIndexByEntry(T pEntry)
{
	for (uint32 i = 0, j = m_vecEntries.size(); i < j; i++)
	{
		if (m_vecEntries[i] == pEntry)
		{
			return i;
		}
	}
	return -1;
}

template <class T>
void				bxcf::CVectorPool<T>::setEntryByIndex(uint32 uiEntryIndex, T pEntry)
{
	m_vecEntries[uiEntryIndex] = pEntry;
}

template <class T>
void				bxcf::CVectorPool<T>::swapEntries(T pEntry1, T pEntry2)
{
	uint32 uiEntryIndex1 = getIndexByEntry(pEntry1);
	uint32 uiEntryIndex2 = getIndexByEntry(pEntry2);
	setEntryByIndex(uiEntryIndex1, pEntry2);
	setEntryByIndex(uiEntryIndex2, pEntry1);
}

template <class T>
void				bxcf::CVectorPool<T>::moveEntryToPosition(T pEntry, uint32 uiPosition)
{
	m_vecEntries.erase(m_vecEntries.begin() + getIndexByEntry(pEntry));
	m_vecEntries.insert(m_vecEntries.begin() + uiPosition, pEntry);
}