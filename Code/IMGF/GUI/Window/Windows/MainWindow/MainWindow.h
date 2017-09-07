#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Window/Window.h"
#include <string>
#include <vector>

class imgf::MainLayer;
class imgf::IMGEditor;
class bxgx::ProgressBar;
class bxgx::TabBar;
class bxgx::Button;
class bxgx::Menu;

class imgf::MainWindow : public bxgx::Window
{
public:
	MainWindow(void);

	void					init(void);

	void					setMainMenuType(imgf::mainLayer::mainMenuType::EMainMenuType uiMainMenuType);

	MainLayer*				getMainLayer(void) { return m_pMainLayer; }
	MainLayerNoTabsOpen*	getMainLayerNoTabsOpen(void) { return m_pMainLayerNoTabsOpen; }
	IMGEditor*				getIMGEditor(void) { return m_pIMGEditor; }

	bxgx::ProgressBar*		getProgressBar(void);
	bxgx::TabBar*			getTabBar(void);

	void					repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

private:
	void					initWindow(void);
	void					initLayers(void);

	void					initMainLayer(void);
	void					initMainLayerNoTabsOpen(void);
	void					initMainMenuLayers(void);
	void					initSettingsMenuLayer(void);
	void					initEditors(void);

public:
	MainLayer*				m_pMainLayer;
	MainLayerNoTabsOpen*	m_pMainLayerNoTabsOpen;
	IMGEditor*				m_pIMGEditor;
	bxgx::Menu*				m_pSettingsMenu;

private:
	imgf::mainLayer::mainMenuType::EMainMenuType	m_uiMainMenuType;
};