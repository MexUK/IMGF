#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Window/Window.h"
#include "GUI/Layer/Layers/DumpWindow/DumpWindowResult.h"
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

	void					setActiveEditor(Editor *pActiveEditor) { m_pActiveEditor = pActiveEditor; }
	Editor*					getActiveEditor(void) { return m_pActiveEditor; }

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

	template <class T>
	T*						addEditor(void);

public:
	MainLayer*				m_pMainLayer;
	MainLayerNoTabsOpen*	m_pMainLayerNoTabsOpen;
	IMGEditor*				m_pIMGEditor;
	TextureEditor*			m_pTextureEditor;
	bxgx::Menu*				m_pSettingsMenu;
	DumpWindowResult		m_dumpWindowResult;
	Editor*					m_pActiveEditor;

private:
	imgf::mainLayer::mainMenuType::EMainMenuType	m_uiMainMenuType;
};

template <class T>
T*							imgf::MainWindow::addEditor(void)
{
	T *pEditor = addLayer<T>(-1, false);
	pEditor->setMainWindow(this);
	pEditor->init();
	return pEditor;
}