#ifndef CSortMenuItem_H
#define CSortMenuItem_H

struct CSortMenuItem
{
	CSortMenuItem(uint32 uiMenuHandle, CSortPriority* pPriority, CSortType* pType) :
		m_uiMenuHandle(uiMenuHandle),
		m_pPriority(pPriority),
		m_pType(pType)
	{};

	void				unload(void) {}

	uint32		m_uiMenuHandle;
	CSortPriority*		m_pPriority;
	CSortType*			m_pType;
};

#endif