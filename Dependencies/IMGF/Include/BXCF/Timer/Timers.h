#pragma once

#include "nsbxcf.h"
#include "Pool/VectorPool.h"
#include "Timer/Timer.h"
#include "Object/Singleton.h"
#include <thread>

template <typename TReturn, class TStruct, typename ...Args>
class bxcf::Timers : public VectorPool<bxcf::Timer<TReturn, TStruct, Args...>*>, public Singleton<bxcf::Timers<TReturn, TStruct, Args...>>
{
public:
	Timers(void);

	static Timer<TReturn, TStruct, Args...>*		add(TReturn(TStruct::*_function)(Args...), uint32 uiInterval, uint32 uiRepetitions, TStruct *pObject, Args... arguments);
	//static Timer<TReturn, void, Args...>*			add(TReturn(*_function)(Args...), uint32 uiInterval, uint32 uiRepetitions, Args... arguments);
	static void										remove(Timer<TReturn, TStruct, Args...> *pTimer);

	void									process(void);

	void									setThreadMarkedToStop(bool bThreadMarkedToStop) { m_bThreadMarkedToStop = bThreadMarkedToStop; }
	bool									isThreadMarkedToStop(void) { return m_bThreadMarkedToStop; }

	void									stopThread(void);

private:
	void									startThread(void);
	bool									isThreadActive(void) { return m_bTimerProcessingThreadActive; }

private:
	bool									m_bTimerProcessingThreadActive;
	bool									m_bThreadMarkedToStop;
	std::thread								m_tTimerProcessing;
};

// constructor/destructor
template <typename TReturn, class TStruct, typename ...Args>
bxcf::Timers<TReturn, TStruct, Args...>::Timers(void) :
	m_bTimerProcessingThreadActive(false),
	m_bThreadMarkedToStop(false)
{
}

// timer processing thread
template <typename TReturn, class TStruct, typename ...Args>
void										bxcf::Timers<TReturn, TStruct, Args...>::startThread(void)
{
	m_bTimerProcessingThreadActive = true;
	m_tTimerProcessing = std::thread([](void) -> void {
		Timers::get()->process();
	});
}

template <typename TReturn, class TStruct, typename ...Args>
void										bxcf::Timers<TReturn, TStruct, Args...>::stopThread(void)
{
	m_bTimerProcessingThreadActive = false;
	m_bThreadMarkedToStop = false;
	m_tTimerProcessing.join();
}

// add/remove timer
template <typename TReturn, class TStruct, typename ...Args>
bxcf::Timer<TReturn, TStruct, Args...>*		bxcf::Timers<TReturn, TStruct, Args...>::add(TReturn(TStruct::*_function)(Args...), uint32 uiInterval, uint32 uiRepetitions, TStruct *pObject, Args... arguments)
{
	Timers *pTimers = Timers::get();
	uint32 uiTimeNow = GetTickCount();
	Timer<TReturn, TStruct, Args...> *pTimer = new Timer<TReturn, TStruct, Args...>;
	pTimer->setInterval(uiInterval);
	pTimer->setRepetitions(uiRepetitions);
	pTimer->setNextCallTime(uiTimeNow + uiInterval);
	pTimer->setRepetitionsLeft(uiRepetitions == 0 ? -1 : uiRepetitions);
	pTimer->setObject(pObject);
	pTimer->setFunction(_function);
	pTimer->setArguments(std::make_tuple(arguments...));
	pTimers->addEntry(pTimer);
	if (!pTimers->isThreadActive())
	{
		pTimers->startThread();
	}
	return pTimer;
}

/*
template <typename TReturn, class TStruct, typename ...Args>
bxcf::Timer<TReturn, void, Args...>*		bxcf::Timers<TReturn, void, Args...>::add(TReturn(*_function)(Args...), uint32 uiInterval, uint32 uiRepetitions, Args... arguments)
{
	Timers *pTimers = Timers::get();
	uint32 uiTimeNow = GetTickCount();
	Timer<TReturn, TStruct, Args...> *pTimer = new Timer<TReturn, void, Args...>;
	pTimer->setInterval(uiInterval);
	pTimer->setRepetitions(uiRepetitions);
	pTimer->setNextCallTime(uiTimeNow + uiInterval);
	pTimer->setRepetitionsLeft(uiRepetitions);
	pTimer->setFunction(_function);
	pTimer->setArguments(std::forward_as_tuple(arguments...));
	pTimers->addEntry(pTimer);
	if (!pTimers->isThreadActive())
	{
		pTimers->startThread();
	}
	return pTimer;
}
*/

template <typename TReturn, class TStruct, typename ...Args>
void										bxcf::Timers<TReturn, TStruct, Args...>::remove(bxcf::Timer<TReturn, TStruct, Args...> *pTimer)
{
	Timers *pTimers = Timers::get();
	pTimers->removeEntry(pTimer);
	if (pTimers->getEntryCount() == 0)
	{
		pTimers->setThreadMarkedToStop(true);
	}
}

// timer processing
template <typename TReturn, class TStruct, typename ...Args>
void										bxcf::Timers<TReturn, TStruct, Args...>::process(void)
{
	while(m_bTimerProcessingThreadActive)
	{
		uint32 uiTimeNow = GetTickCount();
		for (Timer<TReturn, TStruct, Args...> *pTimer : getEntries())
		{
			if (pTimer->getRepetitionsLeft() != 0 && pTimer->getNextCallTime() <= uiTimeNow)
			{
				pTimer->call();
			}
		}
		Sleep(1);
	}
}