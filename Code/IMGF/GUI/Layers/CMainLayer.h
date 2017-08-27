#pragma once

#include "nsbxgx.h"
#include "Layer/CLayer.h"
#include "Event/Events.h"

class CMainWindow;
class bxgx::CTabBarControl;
class bxgx::CProgressControl;
class bxgx::CTextBoxControl;
class bxgx::CDropControl;
class bxgx::CButtonControl;
class bxgx::CLineShape;
class bxgx::CTabBarControlEntry;

class CMainLayer : public bxgx::CLayer, public bxcf::EventBindable
{
public:
	void						init(void);

	void						setIMGFWindow(CMainWindow* pIMGFWindow) { m_pMainWindow = pIMGFWindow; }
	CMainWindow*				getIMGFWindow(void) { return m_pMainWindow; }

	bxgx::CTabBarControl*		getTabBar(void) { return m_pTabBar; }
	bxgx::CProgressControl*		getProgressBar(void) { return m_pProgressBar; }

	void						onChangeTab(bxgx::CTabBarControl *pTabBar);
	void						onRemoveTab(bxgx::CTabBarControlEntry *pTab);

private:
	void						addControls(void);
	void						initControls(void);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

public:
	CMainWindow*				m_pMainWindow;

	bxgx::CTabBarControl*		m_pTabBar;
	bxgx::CProgressControl*		m_pProgressBar;
	bxgx::CTextBoxControl*		m_pSearchBox;

	bxgx::CButtonControl*		m_pSettingsButton;
	bxgx::CLineShape*			m_pSettingsButtonLine1;
	bxgx::CLineShape*			m_pSettingsButtonLine2;
	bxgx::CLineShape*			m_pSettingsButtonLine3;

	bxgx::CTextControl*			m_pText_Game;
	bxgx::CTextControl*			m_pText_GameValidity;
	bxgx::CTextControl*			m_pText_GameLocation;
	bxgx::CTextControl*			m_pText_FileGame;
	bxgx::CTextControl*			m_pText_FileValidity;
	bxgx::CTextControl*			m_pText_FileLocation;
};