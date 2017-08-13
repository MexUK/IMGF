#pragma once

#include "Layer/CGUILayer.h"

class CMainWindow;
class CTabBarControl;
class CProgressControl;
class CTextBoxControl;
class CDropControl;
class CButtonControl;
class CLineShape;

class CMainLayer : public CGUILayer
{
public:
	void						init(void);

	void						setIMGFWindow(CMainWindow* pIMGFWindow) { m_pIMGFWindow = pIMGFWindow; }
	CMainWindow*				getIMGFWindow(void) { return m_pIMGFWindow; }

	CTabBarControl*				getTabBar(void) { return m_pTabBar; }

private:
	void						addControls(void);
	void						initControls(void);

	void						repositionAndResizeControls(void);

private:
	CMainWindow*				m_pIMGFWindow;
	CTabBarControl*				m_pTabBar;
	CProgressControl*			m_pProgressBar;
	CTextBoxControl*			m_pSearchBox;
	CDropControl*				m_pEntryTypeFilter;
	CDropControl*				m_pEntryVersionFilter;
	CButtonControl*				m_pSettingsButton;
	CLineShape*					m_pSettingsButtonLine1;
	CLineShape*					m_pSettingsButtonLine2;
	CLineShape*					m_pSettingsButtonLine3;
};