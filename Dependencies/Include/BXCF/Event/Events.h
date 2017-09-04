#pragma once

#include "nsbxcf.h"
#include "Event/EventFunction.h"
#include "Event/EventBindable.h"
#include <unordered_map>
#include <vector>
#include <functional>

template <typename TReturn, typename ...Args>
extern std::unordered_map<int, std::vector< bxcf::EventFunction<TReturn, Args...>* >> bxcf::g_eventBoundFunctions;

template <typename TReturn, typename ...Args>
extern std::unordered_map<int, std::vector< bxcf::EventFunction<TReturn, const Args...>* >> bxcf::g_eventBoundFunctionsConst;

struct bxcf::Events
{
	// trigger event for functions without a return
	/*
	template <typename ...Args>
	static bool trigger(int iEvent, Args&&... args)
	{
		if (bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>... >.find(iEvent) == bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>... > *pFuncObject : bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			(object->*func)(args...);
		}
		return true;
	}
	*/

	/*
	template <typename ...Args>
	static bool trigger(int iEvent, Args&&... args)
	{
		if (bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>... >.find(iEvent) == bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>... > *pFuncObject : bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			(object->*func)(args...);
		}
		return true;
	}

	template <typename ...Args>
	static bool trigger(int iEvent, const Args&&... args)
	{
		if (bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>... >.find(iEvent) == bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>... > *pFuncObject : bxcf::g_eventBoundFunctions<void, std::conditional_t<std::is_pointer<std::remove_reference_t<Args>>::value, std::remove_reference_t<Args>, Args>...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			(object->*func)(args...);
		}
		return true;
	}
	*/

	// void returns, const unqualified
	template <typename ...Args>
	static bool triggerConst(int iEvent, const Args... args)
	{
		if (bxcf::g_eventBoundFunctionsConst<void, const Args...>.find(iEvent) == bxcf::g_eventBoundFunctionsConst<void, const Args...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<void, const Args...> *pFuncObject : bxcf::g_eventBoundFunctionsConst<void, const Args...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			(object->*func)(args...);
		}
		return true;
	}

	// void returns, non-const unqualified
	template <typename ...Args>
	static bool trigger(int iEvent, Args... args)
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

	// void returns, non-const reference
	template <typename ...Args>
	static bool triggerRef(int iEvent, Args&... args)
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

	// bool returns, const unqualified
	template <typename TReturn = bool, typename ...Args>
	static bool triggerConstBR(int iEvent, const Args... args)
	{
		if (bxcf::g_eventBoundFunctionsConst<TReturn, const Args...>.find(iEvent) == bxcf::g_eventBoundFunctionsConst<TReturn, const Args...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<TReturn, const Args...> *pFuncObject : bxcf::g_eventBoundFunctionsConst<TReturn, const Args...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			if (!(object->*func)(args...))
			{
				return false;
			}
		}
		return true;
	}

	// bool returns, non-const reference
	template <typename TReturn = bool, typename ...Args>
	static bool triggerBR(int iEvent, Args... args)
	{
		if (bxcf::g_eventBoundFunctions<TReturn, Args...>.find(iEvent) == bxcf::g_eventBoundFunctions<TReturn, Args...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<TReturn, Args...> *pFuncObject : bxcf::g_eventBoundFunctions<TReturn, Args...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			if (!(object->*func)(args...))
			{
				return false;
			}
		}
		return true;
	}

	// bool returns, non-const reference
	template <typename ...Args>
	static bool triggerRefBR(int iEvent, Args&... args)
	{
		if (bxcf::g_eventBoundFunctions<void, Args&...>.find(iEvent) == bxcf::g_eventBoundFunctions<void, Args&...>.end())
		{
			return true;
		}

		for (bxcf::EventFunction<void, Args&...> *pFuncObject : bxcf::g_eventBoundFunctions<void, Args&...>[iEvent])
		{
			bxcf::EventBindable* object = (bxcf::EventBindable*)pFuncObject->m_object;
			auto& func = pFuncObject->m_function;

			if (!(object->*func)(args...))
			{
				return false;
			}
		}
		return true;
	}

	static bool isEventCancelled(void) { return false; }
};