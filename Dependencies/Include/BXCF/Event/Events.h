#pragma once

#include "bxcf.h"
#include <unordered_map>
#include <vector>
#include <functional>

template <class TStruct, typename ...Args>
struct bxcf::EventFunction;
struct bxcf::Events;
template <class TStruct>
struct bxcf::EventBindable;
struct bxcf::EventTriggerable;
template <class TBindableStruct>
struct bxcf::EventUtilizer;

//template <typename ...Args>
//std::unordered_map<int, std::vector< bxcf::EventFunction<Args&...> >> g_eventBoundFunctions;

template <class TStruct, typename ...Args>
extern std::unordered_map<int, std::vector< bxcf::EventFunction<TStruct, Args&...> >> g_eventBoundFunctions;

struct bxcf::EventTriggerable
{
};

template <class TBindableStruct>
struct bxcf::EventUtilizer : public bxcf::EventBindable<TBindableStruct>, public bxcf::EventTriggerable
{
};

template <class TStruct, typename ...Args>
struct bxcf::EventFunction
{
	TStruct* m_object;
	void(TStruct::* __thiscall m_function)(Args&...);

	EventFunction(void)
	{
	}
	EventFunction(void* object, void(TStruct::* __thiscall func)(Args&...)) :
		m_object(object),
		m_function(func)
	{
	}

	void setObject(TStruct *object) { m_object = object; }
	TStruct* getObject(void) { return m_object; }

	void(TStruct::* __thiscall getFunction(void))(Args&...) { return m_function; }
	void setFunction(void(TStruct::* __thiscall func)(Args&...)) { m_function = func; }
};

struct bxcf::Events
{
	template <class TStruct, typename ...Args>
	static void trigger(int iEvent, Args&... args)
	{
		auto f = g_eventBoundFunctions<TStruct, Args&...>;

		if (g_eventBoundFunctions<TStruct, Args&...>.find(iEvent) == g_eventBoundFunctions<TStruct, Args&...>.end())
		{
			return;
		}

		for (auto eventFunctionObject : g_eventBoundFunctions<TStruct, Args&...>[iEvent])
		{
			auto object = /*(bxcf::EventTriggerable*)*/eventFunctionObject.m_object;
			auto func = eventFunctionObject.m_function;

			(object->*func)(args...);

			/*
			CPoint2D point((int32)200, 200);
			uint32 uiECX = (uint32)object;
			uint32 uiFunc = (uint32)&func;
			uint32 uiArg1 = (uint32)&point;
			__asm mov ecx, uiECX
			__asm push uiArg1
			__asm call uiFunc
			//*func(args...);
			*/
		}
	}
};

template <class TStruct>
struct bxcf::EventBindable : public bxcf::EventTriggerable
{
	template <typename ...Args>
	int bind(int iEvent, void(TStruct::* func)(Args&... args))
	{
		/*
		temp
		// initialize template static member property
		if (bxcf::Events::m_eventBoundFunctions<Args&...>.empty())
		{
			bxcf::Events::m_eventBoundFunctions<Args&...> = std::unordered_map<int, std::vector< bxcf::EventFunction<Args&...> >>();
		}
		*/

		bxcf::EventFunction<TStruct, Args&...> funcObject;
		funcObject.m_object = /*(TStruct*)*/ /*dynamic_cast<bxcf::EventTriggerable*>(this)*/ (TStruct*)this;
		funcObject.m_function = /*(void(TStruct::* __thiscall)(Args&... args))*/func;

		//auto vecFunctions = g_eventBoundFunctions<TStruct, Args&...>[iEvent];
		//vecFunctions.insert(vecFunctions.begin() + vecFunctions.size(), funcObject);
		//vecFunctions.push_back(funcObject);
		g_eventBoundFunctions<TStruct, Args&...>[iEvent].push_back(funcObject);

		return g_eventBoundFunctions<TStruct, Args&...>[iEvent].size() - 1;
	}

	template <typename ...Args>
	bool unbind(int iEvent, void(TStruct::* func)(Args&... args))
	{
		if (bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>.find(iEvent) == bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>.end())
		{
			return false;
		}

		int iFuncObjectIndex = getFunctionObjectIndex(iEvent, func);
		if (iFuncObjectIndex == -1)
		{
			return false;
		}

		auto& vecFunctions = bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>[iEvent];
		vecFunctions.erase(vecFunctions.begin() + iFuncObjectIndex);

		return true;
	}

	template <typename ...Args>
	bool unbind(int iEvent)
	{
		if (bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>.find(iEvent) == bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>.end())
		{
			return false;
		}

		bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>.erase(iEvent);
		return true;
	}

	template <typename ...Args>
	bool unbind(void)
	{
		if (bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>.empty())
		{
			return false;
		}

		bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>.clear();
		return true;
	}

	template <typename ...Args>
	static bxcf::EventFunction<TStruct, Args&...>* getFunctionObject(int iEvent, void(TStruct::* func)(Args&... args))
	{
		for (auto& eventFunctionObject : bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>[iEvent])
		{
			if (func == eventFunctionObject.m_function)
			{
				return &eventFunctionObject;
			}
		}

		return nullptr;
	}

	template <typename ...Args>
	static int getFunctionObjectIndex(int iEvent, void(TStruct::* func)(Args&... args))
	{
		int index = 0;
		for (auto& eventFunctionObject : bxcf::Events::g_eventBoundFunctions<TStruct, Args&...>[iEvent])
		{
			if ((void(bxcf::EventTriggerable::* __thiscall)(Args&... args))func == eventFunctionObject.m_function)
			{
				return index;
			}
			index++;
		}

		return -1;
	}
};