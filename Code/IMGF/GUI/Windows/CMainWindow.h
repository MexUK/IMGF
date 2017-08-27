#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Window/CWindow.h"
#include <string>
#include <vector>

class imgf::CMainLayer;
class imgf::CIMGEditor;
class bxgx::CProgressControl;
class bxgx::CTabBarControl;
class bxgx::CButtonControl;

class imgf::CMainWindow : public bxgx::CWindow
{
public:
	CMainWindow(void);

	void					init(void);

	void					setMainMenuType(imgf::mainLayer::mainMenuType::EMainMenuType uiMainMenuType);

	CMainLayer*				getMainLayer(void) { return m_pMainLayer; }
	CIMGEditor*				getIMGEditor(void) { return m_pIMGEditor; }

	bxgx::CProgressControl*	getProgressBar(void);
	bxgx::CTabBarControl*	getTabBar(void);

	void					repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

private:
	void					initWindow(void);
	void					initLayers(void);

	void					initMainLayer(void);
	void					initMainMenuLayers(void);
	void					initSettingsMenuLayer(void);
	void					initEditors(void);

public:
	CMainLayer*								m_pMainLayer;
	CIMGEditor*								m_pIMGEditor;
	std::vector<bxgx::CButtonControl*>		m_vecSettingsMenuButtons;

private:
	imgf::mainLayer::mainMenuType::EMainMenuType	m_uiMainMenuType;
};