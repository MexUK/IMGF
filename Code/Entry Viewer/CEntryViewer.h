#ifndef CEntryViewer_H
#define CEntryViewer_H

#include <Windows.h>
#include "Type/Types.h"
#include <string>

class CEntryViewer
{
public:
	CEntryViewer(void);

	virtual void						reset(void);
	virtual void						prepareRenderData(void) = 0;
	virtual void						render(void) = 0;
	virtual void						loadThreadAndWindow(void) = 0;
	virtual void						unloadThreadAndWindow(void) = 0;
	virtual void						openWindow(void) = 0;
	virtual void						closeWindow(void) = 0;

	void								setWindowIsOpen(bool bWindowIsOpen) { m_bWindowIsOpen = bWindowIsOpen; }
	bool								isWindowOpen(void) { return m_bWindowIsOpen; }

	void								setWindowTitle(std::string strWindowTitle) { m_strWindowTitle = strWindowTitle; }
	std::string							getWindowTitle(void) { return m_strWindowTitle; }

	void								setThread(HANDLE hThread) { m_hThread = hThread; }
	HANDLE								getThread(void) { return m_hThread; }

	void								setEntityDataIsCorrupt(bool bEntityDataIsCorrupt) { m_bEntityDataIsCorrupt = bEntityDataIsCorrupt; }
	bool								isEntityDataCorrupt(void) { return m_bEntityDataIsCorrupt; }

	void								setRenderDataIsReady(bool bRenderDataIsReady) { m_bRenderDataIsReady = bRenderDataIsReady; }
	bool								isRenderDataReady(void) { return m_bRenderDataIsReady; }

private:
	HANDLE								m_hThread;
	uint8								m_bWindowIsOpen : 1;
	uint8								m_bEntityDataIsCorrupt : 1;
	uint8								m_bRenderDataIsReady : 1;
	std::string							m_strWindowTitle;
};

#endif