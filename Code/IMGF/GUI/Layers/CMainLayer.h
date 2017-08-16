#pragma once

#include "Layer/CGUILayer.h"
#include "Event/Events.h"

class CMainWindow;
class CTabBarControl;
class CProgressControl;
class CTextBoxControl;
class CDropControl;
class CButtonControl;
class CLineShape;
class CTabBarControlEntry;

class CMainLayer : public CGUILayer, public bxcf::EventBindable
{
public:
	void						init(void);

	void						setIMGFWindow(CMainWindow* pIMGFWindow) { m_pMainWindow = pIMGFWindow; }
	CMainWindow*				getIMGFWindow(void) { return m_pMainWindow; }

	CTabBarControl*				getTabBar(void) { return m_pTabBar; }
	CProgressControl*			getProgressBar(void) { return m_pProgressBar; }

	void						onChangeTab(CTabBarControl *pTabBar);
	void						onRemoveTab(CTabBarControlEntry *pTab);

private:
	void						addControls(void);
	void						initControls(void);

	void						repositionAndResizeControls(void);

public:
	CMainWindow*				m_pMainWindow;

	CTabBarControl*				m_pTabBar;
	CProgressControl*			m_pProgressBar;
	CTextBoxControl*			m_pSearchBox;
	CDropControl*				m_pEntryTypeFilter;
	CDropControl*				m_pEntryVersionFilter;

	CButtonControl*				m_pSettingsButton;
	CLineShape*					m_pSettingsButtonLine1;
	CLineShape*					m_pSettingsButtonLine2;
	CLineShape*					m_pSettingsButtonLine3;

	CTextControl*				m_pText_Game;
	CTextControl*				m_pText_GameValidity;
	CTextControl*				m_pText_GameLocation;
	CTextControl*				m_pText_FileGame;
	CTextControl*				m_pText_FileValidity;
	CTextControl*				m_pText_FileLocation;
};