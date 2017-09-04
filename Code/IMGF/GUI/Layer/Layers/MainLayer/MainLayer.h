#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::MainWindow;
class bxgx::TabBar;
class bxgx::ProgressBar;
class bxgx::TextBox;
class bxgx::DropDown;
class bxgx::Button;
class bxgx::Line;
class bxgx::Tab;

class imgf::MainLayer : public bxgx::Layer, public bxcf::EventBindable
{
public:
	void						init(void);

	void						setIMGFWindow(MainWindow* pIMGFWindow) { m_pMainWindow = pIMGFWindow; }
	MainWindow*					getIMGFWindow(void) { return m_pMainWindow; }

	bxgx::TabBar*				getTabBar(void) { return m_pTabBar; }
	bxgx::ProgressBar*			getProgressBar(void) { return m_pProgressBar; }

	void						onChangeTab(bxgx::TabBar *pTabBar);
	void						onRemoveTab(bxgx::Tab *pTab);

private:
	void						addControls(void);
	void						initControls(void);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

public:
	MainWindow*					m_pMainWindow;

	bxgx::TabBar*				m_pTabBar;
	bxgx::ProgressBar*			m_pProgressBar;
	bxgx::TextBox*				m_pSearchBox;

	bxgx::Button*				m_pSettingsButton;
	bxgx::Line*					m_pSettingsButtonLine1;
	bxgx::Line*					m_pSettingsButtonLine2;
	bxgx::Line*					m_pSettingsButtonLine3;

	bxgx::Text*					m_pText_Game;
	bxgx::Text*					m_pText_GameValidity;
	bxgx::Text*					m_pText_GameLocation;
	bxgx::Text*					m_pText_FilEGame;
	bxgx::Text*					m_pText_FileValidity;
	bxgx::Text*					m_pText_FileLocation;
};