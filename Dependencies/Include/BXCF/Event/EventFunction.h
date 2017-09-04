#pragma once

#include "nsbxcf.h"

template <typename TReturn, typename ...Args>
struct bxcf::EventFunction
{
	void*							m_object;
	TReturn(bxcf::EventBindable::*	m_function)(Args...);

	EventFunction(void)
	{
	}

	EventFunction(void* object, TReturn(bxcf::EventBindable::* func)(Args...)) :
		m_object(object),
		m_function(func)
	{
	}

	void setObject(void *object) { m_object = object; }
	void* getObject(void) { return m_object; }

	TReturn(bxcf::EventBindable::* __thiscall getFunction(void))(Args...) { return m_function; }
	void setFunction(TReturn(bxcf::EventBindable::* func)(Args...)) { m_function = func; }
};