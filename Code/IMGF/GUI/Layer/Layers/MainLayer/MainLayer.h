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
class bxgx::Menu;

class imgf::MainLayer : public bxgx::Layer, public bxcf::EventBindable
{
public:
	MainLayer(void);

	void						init(void);

	void						setIMGFWindow(MainWindow* pIMGFWindow) { m_pMainWindow = pIMGFWindow; }
	MainWindow*					getIMGFWindow(void) { return m_pMainWindow; }

	bxgx::TabBar*				getTabBar(void) { return m_pTabBar; }

	void						onChangeTab(bxgx::TabBar *pTabBar);
	void						onRemoveTab(bxgx::Tab *pTab);

private:
	void						addControls(void);
	void						initControls(void);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

public:
	MainWindow*					m_pMainWindow;

	bxgx::TabBar*				m_pTabBar;

	bxgx::Button*				m_pSettingsButton;
	bxgx::Line*					m_pSettingsButtonLine1;
	bxgx::Line*					m_pSettingsButtonLine2;
	bxgx::Line*					m_pSettingsButtonLine3;

	bxgx::Text*					m_pText_FilePath;
	bxgx::Text*					m_pText_FileVersion;
	bxgx::Text*					m_pText_FileGame;
	bxgx::Text*					m_pText_FileEntryCount;

	bxgx::Menu*					m_pRecentlyOpenMenu;
};