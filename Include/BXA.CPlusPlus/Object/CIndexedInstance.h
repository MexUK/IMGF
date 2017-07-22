#ifndef CIndexedInstance_H
#define CIndexedInstance_H

#include "BXA.h"
#include <vector>

template<class Class>
class bxa::CIndexedInstance
{
public:
	static Class*						getInstance(uint32 uiInstanceIndex = 0);
	static std::vector<Class*>&			getInstances(void) { return m_vecInstances; }

private:
	static std::vector<Class*>			m_vecInstances;
};

template <class Class>
std::vector<Class*>						bxa::CIndexedInstance<Class>::m_vecInstances;

template <class Class>
Class*									bxa::CIndexedInstance<Class>::getInstance(uint32 uiInstanceIndex)
{
	if (uiInstanceIndex >= m_vecInstances.size())
	{
		m_vecInstances.resize(uiInstanceIndex + 1);
		m_vecInstances[uiInstanceIndex] = new Class;
	}
	return m_vecInstances[uiInstanceIndex];
}

#endif