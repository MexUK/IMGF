#pragma once

#include "nsbxcf.h"
#include <tuple>

template <typename F, typename O, typename Tuple>
void call(F f, Tuple && t);

template <typename TReturn, class TStruct, typename ...Args>
class bxcf::Timer
{
public:
	Timer(void);

	void					setInterval(uint32 uiInterval) { m_uiInterval = uiInterval; }
	uint32					getInterval(void) { return m_uiInterval; }

	void					setRepetitions(uint32 uiRepetitions) { m_uiRepetitions = uiRepetitions; }
	uint32					getRepetitions(void) { return m_uiRepetitions; }
	
	void					setNextCallTime(uint32 uiNextCallTime) { m_uiNextCallTime = uiNextCallTime; }
	uint32					getNextCallTime(void) { return m_uiNextCallTime; }

	void					setRepetitionsLeft(uint32 uiRepetitionsLeft) { m_uiRepetitionsLeft = uiRepetitionsLeft; }
	uint32					getRepetitionsLeft(void) { return m_uiRepetitionsLeft; }

	void					setObject(void* pObject) { m_pObject = pObject; }
	void*					getObject(void) { return m_pObject; }

	void					setFunction(TReturn(TStruct::* _function)(Args...)) { m_function = _function; }
	TReturn(TStruct::*		getFunction(Args...)) (void) { return m_function; }
	
	//void					setArguments(Args... arguments) { m_tupArguments = std::make_tuple(arguments...); }
	void					setArguments(std::tuple<Args...>& tupArguments) { m_tupArguments = tupArguments; }
	std::tuple<Args...>&	getArguments(void) { return m_tupArguments; }
	
	void					call(void);

private:
	uint32					m_uiInterval;
	uint32					m_uiRepetitions;
	uint32					m_uiNextCallTime;
	uint32					m_uiRepetitionsLeft;
	void*					m_pObject;
	TReturn(TStruct::*		m_function)(Args...);
	std::tuple<Args...>		m_tupArguments;
};

template <typename TReturn, class TStruct, typename ...Args>
bxcf::Timer<TReturn, TStruct, Args...>::Timer(void) :
	m_uiInterval(0),
	m_uiRepetitions(0),
	m_uiNextCallTime(0),
	m_uiRepetitionsLeft(0),
	m_pObject(nullptr)
{
}

template <typename TReturn, class TStruct, typename ...Args>
void										bxcf::Timer<TReturn, TStruct, Args...>::call(void)
{
	//((TStruct*)m_pObject)->*m_function(std::forward<Args...>(m_tupArguments));
	::call(m_function, (TStruct*)m_pObject, m_tupArguments);

	if (m_uiRepetitions != 0)
	{
		m_uiRepetitionsLeft--;
	}

	uint32 uiTimeNow = GetTickCount();
	m_uiNextCallTime = uiTimeNow + m_uiInterval;
}

// https://stackoverflow.com/questions/10766112/c11-i-can-go-from-multiple-args-to-tuple-but-can-i-go-from-tuple-to-multiple
// implementation details, users never invoke these directly
namespace detail
{
	template <typename F, typename O, typename Tuple, bool Done, int Total, int... N>
	struct call_impl
	{
		static void call(F f, O *pObject, Tuple && t)
		{
			call_impl<F, O, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(f, pObject, std::forward<Tuple>(t));
		}
	};

	template <typename F, typename O, typename Tuple, int Total, int... N>
	struct call_impl<F, O, Tuple, true, Total, N...>
	{
		static void call(F f, O *pObject, Tuple && t)
		{
			(((O*)pObject)->*f)(std::get<N>(std::forward<Tuple>(t))...);
		}
	};
}

// user invokes this
template <typename F, typename O, typename Tuple>
void call(F f, O *pObject, Tuple && t)
{
	typedef typename std::decay<Tuple>::type ttype;
	detail::call_impl<F, O, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(f, pObject, std::forward<Tuple>(t));
}