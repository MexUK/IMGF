#pragma once

#include "nsbxcf.h"
#include <vector>

template<class Class>
class bxcf::IndexedInstance
{
public:
	static Class*						get(uint32 uiInstanceIndex = 0);
	static std::vector<Class*>&			gets(void) { return m_vecInstances; }

private:
	static std::vector<Class*>			m_vecInstances;
};

template <class Class>
std::vector<Class*>						bxcf::IndexedInstance<Class>::m_vecInstances;

template <class Class>
Class*									bxcf::IndexedInstance<Class>::get(uint32 uiInstanceIndex)
{
	if (uiInstanceIndex >= m_vecInstances.size())
	{
		m_vecInstances.resize(uiInstanceIndex + 1);
		m_vecInstances[uiInstanceIndex] = new Class;
	}
	return m_vecInstances[uiInstanceIndex];
}