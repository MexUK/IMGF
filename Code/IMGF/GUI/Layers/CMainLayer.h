#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/CLayer.h"
#include "Event/Events.h"

class imgf::CMainWindow;
class bxgx::CTabBar;
class bxgx::CProgressBar;
class bxgx::CTextBox;
class bxgx::CDropDown;
class bxgx::CButton;
class bxgx::CLine;
class bxgx::CTab;

class imgf::CMainLayer : public bxgx::CLayer, public bxcf::EventBindable
{
public:
	void						init(void);

	void						setIMGFWindow(CMainWindow* pIMGFWindow) { m_pMainWindow = pIMGFWindow; }
	CMainWindow*				getIMGFWindow(void) { return m_pMainWindow; }

	bxgx::CTabBar*		getTabBar(void) { return m_pTabBar; }
	bxgx::CProgressBar*		getProgressBar(void) { return m_pProgressBar; }

	void						onChangeTab(bxgx::CTabBar *pTabBar);
	void						onRemoveTab(bxgx::CTab *pTab);

private:
	void						addControls(void);
	void						initControls(void);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

public:
	CMainWindow*				m_pMainWindow;

	bxgx::CTabBar*		m_pTabBar;
	bxgx::CProgressBar*		m_pProgressBar;
	bxgx::CTextBox*		m_pSearchBox;

	bxgx::CButton*		m_pSettingsButton;
	bxgx::CLine*			m_pSettingsButtonLine1;
	bxgx::CLine*			m_pSettingsButtonLine2;
	bxgx::CLine*			m_pSettingsButtonLine3;

	bxgx::CText*			m_pText_Game;
	bxgx::CText*			m_pText_GameValidity;
	bxgx::CText*			m_pText_GameLocation;
	bxgx::CText*			m_pText_FileGame;
	bxgx::CText*			m_pText_FileValidity;
	bxgx::CText*			m_pText_FileLocation;
};