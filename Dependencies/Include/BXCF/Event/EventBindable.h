#pragma once

#include "nsbxcf.h"

struct bxcf::EventBindable
{
	/*
	// non-const, void return
	template <class TStruct, typename ...Args>
	int bindEvent(int iEvent, void(TStruct::* func)(Args...))
	{
		bxcf::EventFunction<void, Args...> *pFuncObject = new bxcf::EventFunction<void, Args...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (void(bxcf::EventBindable::*)(Args...))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<void, Args...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}
	*/

	// non-const, bool return
	template <typename TReturn, class TStruct, typename ...Args>
	int bindEvent(int iEvent, TReturn(TStruct::* func)(Args...))
	{
		bxcf::EventFunction<TReturn, Args...> *pFuncObject = new bxcf::EventFunction<TReturn, Args...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (TReturn(bxcf::EventBindable::*)(Args...))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<TReturn, Args...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}

	// non-const, reference, bool return
	template <typename TReturn, class TStruct, typename ...Args>
	int bindEventRef(int iEvent, TReturn(TStruct::* func)(Args&...))
	{
		bxcf::EventFunction<TReturn, Args&...> *pFuncObject = new bxcf::EventFunction<TReturn, Args&...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (TReturn(bxcf::EventBindable::*)(Args&...))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctions<TReturn, Args&...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}

	/*
	// const, void return
	template <class TStruct, typename ...Args>
	int bindEventConst(int iEvent, void(TStruct::* func)(const Args...))
	{
		bxcf::EventFunction<void, const Args...> *pFuncObject = new bxcf::EventFunction<void, const Args...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (void(bxcf::EventBindable::*)(const Args...))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctionsConst<void, const Args...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}
	*/

	// const, bool return
	template <typename TReturn, class TStruct, typename ...Args>
	int bindEventConst(int iEvent, TReturn(TStruct::* func)(const Args...))
	{
		bxcf::EventFunction<TReturn, const Args...> *pFuncObject = new bxcf::EventFunction<TReturn, const Args...>;
		pFuncObject->m_object = (TStruct*)this;
		pFuncObject->m_function = (TReturn(bxcf::EventBindable::*)(const Args...))func;

		auto& vecFunctions = bxcf::g_eventBoundFunctionsConst<TReturn, const Args...>[iEvent];
		vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), pFuncObject);

		return vecFunctions.size() - 1;
	}
};