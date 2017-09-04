#pragma once

#include "nsbxcf.h"

template<class SingletonClass>
class bxcf::Singleton
{
public:
	bxcf::Singleton<SingletonClass>(void);
	static SingletonClass*				get(void);

private:
	static SingletonClass*				m_pInstance;
};

// member property
template <class SingletonClass>
SingletonClass*							bxcf::Singleton<SingletonClass>::m_pInstance = nullptr;

// constructor
template <class SingletonClass>
bxcf::Singleton<SingletonClass>::Singleton(void)
{
	// store instance into singleton member property, as the coder may use "new Class" or "Class objectName" instead of "Class::get()"
	m_pInstance = (SingletonClass*) this;
}

// get instance
template <class SingletonClass>
SingletonClass*							bxcf::Singleton<SingletonClass>::get(void)
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SingletonClass;
	}
	return m_pInstance;
}