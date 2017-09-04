#pragma once

#include "nsbxcf.h"

template<class SingletonClass>
class bxcf::CSingleton
{
public:
	bxcf::CSingleton<SingletonClass>(void);
	static SingletonClass*				get(void);

private:
	static SingletonClass*				m_pInstance;
};

// member property
template <class SingletonClass>
SingletonClass*							bxcf::CSingleton<SingletonClass>::m_pInstance = nullptr;

// constructor
template <class SingletonClass>
bxcf::CSingleton<SingletonClass>::CSingleton(void)
{
	// store instance into singleton member property, as the coder may use "new Class" or "Class objectName" instead of "Class::get()"
	m_pInstance = (SingletonClass*) this;
	//m_pInstance = (CSingleton*) this;
	//m_pInstance = (bxcf::CSingleton<SingletonClass>*) this;
}

// get instance
template <class SingletonClass>
SingletonClass*							bxcf::CSingleton<SingletonClass>::get(void)
{
	//return new SingletonClass;
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SingletonClass;
	}
	return m_pInstance;
}