#pragma once

#include "nsbxcf.h"
#include <unordered_map>
#include <vector>
#include <functional>

template <typename TReturn, typename ...Args>
struct bxcf::EventFunction;
struct bxcf::Events;
struct bxcf::EventBindable;

// data
template <typename TReturn, typename ...Args>
struct bxcf::EventFunction
{
	void* m_object;
	TReturn(bxcf::EventBindable::* m_function)(Args...);

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

// storage
template <typename TReturn, typename ...Args>
extern std::unordered_map<int, std::vector< bxcf::EventFunction<TReturn, Args...>* >> bxcf::g_eventBoundFunctions;

// trigger
struct bxcf::Events
{
	template <typename TReturn, typename ...Args>
	static bool trigger(int iEvent, Args... args) // dynamic return, regular parameters
	{
		if (bxcf::g_eventBoundFunctions<TReturn, Args...>.find(iEvent) == bxcf::g_eventBoundFunctions<TReturn, Args...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<TReturn, Args...> *pFuncObject : bxcf::g_eventBoundFunctions<TReturn, Args...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			if ((object->*func)(args...))
			{
				return true;
			}
		}
		return true;
	}

	template <typename ...Args>
	static bool trigger(int iEvent, Args&... args) // dynamic return, reference parameters
	{
		if (bxcf::g_eventBoundFunctions<void, Args&...>.find(iEvent) == bxcf::g_eventBoundFunctions<void, Args&...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<void, Args&...> *pFuncObject : bxcf::g_eventBoundFunctions<void, Args&...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			(object->*func)(args...);
		}
		return true;
	}

	template <typename ...Args>
	static bool triggerVoidNoRef(int iEvent, Args... args) // void return, regular parameters
	{
		if (bxcf::g_eventBoundFunctions<void, Args...>.find(iEvent) == bxcf::g_eventBoundFunctions<void, Args...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<void, Args...> *pFuncObject : bxcf::g_eventBoundFunctions<void, Args...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			(object->*func)(args...);
		}
		return true;
	}

	static bool isEventCancelled(void) { return false; }
};

// bind
struct bxcf::EventBindable
{
	template <typename TReturn, class TStruct, typename ...Args>
	int bindEvent(int iEvent, TReturn(TStruct::* func)(Args... args)) // dynamic return, regular parameters
	{
		bxcf::EventFunction<TReturn, Args...> *pFuncObject = new bxcf::EventFunction<TReturn, Args...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (TReturn(bxcf::EventBindable::*)(Args... args))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<TReturn, Args...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}

	template <typename TReturn, class TStruct, typename ...Args>
	int bindEvent(int iEvent, TReturn(TStruct::* func)(Args&... args)) // dynamic return, reference parameters
	{
		bxcf::EventFunction<TReturn, Args&...> *pFuncObject = new bxcf::EventFunction<TReturn, Args&...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (TReturn(bxcf::EventBindable::*)(Args&... args))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<TReturn, Args&...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}

	template <class TStruct, typename ...Args>
	int bindEventVoidNoRef(int iEvent, void(TStruct::* func)(Args... args)) // void return, regular parameters
	{
		bxcf::EventFunction<void, Args...> *pFuncObject = new bxcf::EventFunction<void, Args...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (void(bxcf::EventBindable::*)(Args... args))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<void, Args...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}

	template <class TStruct, typename ...Args>
	int bindEventVoidRef(int iEvent, void(TStruct::* func)(Args&... args)) // void return, reference parameters
	{
		bxcf::EventFunction<void, Args&...> *pFuncObject = new bxcf::EventFunction<void, Args&...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (void(bxcf::EventBindable::*)(Args&... args))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<void, Args&...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}
};