#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::MainWindow;
class bxgx::TabBar;
class bxgx::ProgressBar;
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

	void						onChangeTab(bxgx::TabBar *pTabBar);
	void						onRemoveTab(bxgx::Tab *pTab);

	void						addMenus(void);
	void						removeMenus(void);
	void						setCertainMenuItemsEnabled(bool bEnabled);

private:
	void						addControls(void);
	void						initControls(void);

	void						onResizeWindow(bxcf::Vec2i& vecSizeDifference);

public:
	MainWindow*					m_pMainWindow;

	bxgx::Button*				m_pSettingsButton;
	bxgx::Line*					m_pSettingsButtonLine1;
	bxgx::Line*					m_pSettingsButtonLine2;
	bxgx::Line*					m_pSettingsButtonLine3;

	bxgx::Menu*					m_pRecentlyOpenMenu;
	bxgx::Menu*					m_pFileGroupMenu;
};