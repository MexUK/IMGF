#ifndef CSingleton_H
#define CSingleton_H

#include "BXA.h"

template<class SingletonClass>
class bxa::CSingleton
{
public:
	static SingletonClass*				getInstance(void);

private:
	static SingletonClass*				m_pInstance;
};

template <class SingletonClass>
SingletonClass*							bxa::CSingleton<SingletonClass>::m_pInstance = nullptr;

template <class SingletonClass>
SingletonClass*							bxa::CSingleton<SingletonClass>::getInstance(void)
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SingletonClass;
	}
	return m_pInstance;
}

#endif