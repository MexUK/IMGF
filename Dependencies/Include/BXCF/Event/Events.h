#pragma once

#include "bxcf.h"
#include <unordered_map>
#include <vector>
#include <functional>

template <typename ...Args>
struct bxcf::EventFunction;
struct bxcf::Events;
//template <class TStruct>
struct bxcf::EventBindable;
struct bxcf::EventTriggerable;

// data
template <typename ...Args>
struct bxcf::EventFunction
{
	void* m_object;
	void(bxcf::EventBindable::* __thiscall m_function)(Args...);

	EventFunction(void)
	{
	}
	EventFunction(void* object, void(bxcf::EventBindable::* __thiscall func)(Args...)) :
		m_object(object),
		m_function(func)
	{
	}

	void setObject(void *object) { m_object = object; }
	void* getObject(void) { return m_object; }

	void(bxcf::EventBindable::* __thiscall getFunction(void))(Args...) { return m_function; }
	void setFunction(void(bxcf::EventBindable::* __thiscall func)(Args...)) { m_function = func; }
};

// storage
template <typename ...Args>
extern std::unordered_map<int, std::vector< bxcf::EventFunction<Args...>* >> bxcf::g_eventBoundFunctions;

// trigger
struct bxcf::Events
{
	template <typename ...Args>
	static void trigger(int iEvent, Args... args)
	{
		if (bxcf::g_eventBoundFunctions<Args...>.find(iEvent) == bxcf::g_eventBoundFunctions<Args...>.end())
		{
			return;
		}

		for (bxcf::EventFunction<Args...> *pFuncObject : bxcf::g_eventBoundFunctions<Args...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			(object->*func)(args...);
		}
	}

	static bool isEventCancelled(void) { return false; }
};

// bind
//template <class TStruct>
struct bxcf::EventBindable
{
	template <class TStruct, typename ...Args>
	int bindEvent(int iEvent, void(TStruct::* func)(Args... args))
	{
		bxcf::EventFunction<Args...> *pFuncObject = new bxcf::EventFunction<Args...>;
		pFuncObject->m_object = (TStruct*)this;
		//pFuncObject.m_function = (void(bxcf::EventBindable<TStruct>::* __thiscall)(Args... args))func;
		//pFuncObject->m_function = (void(TStruct::* __thiscall)(Args... args))func;
		pFuncObject->m_function = (void(bxcf::EventBindable::* __thiscall)(Args... args))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<Args...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}
};

// blank class - classes with a method for invoking via trigger() do NOT need to inherit this class
struct bxcf::EventTriggerable
{
};