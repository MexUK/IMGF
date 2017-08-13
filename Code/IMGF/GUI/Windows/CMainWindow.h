#pragma once

#include "imgf.h"
#include "Window/CWindow.h"
#include <string>
#include <vector>

class CMainLayer;
class CIMGEditor;

class CMainWindow : public CWindow
{
public:
	CMainWindow(void);

	void					init(void);

	void					setMainMenuType(imgf::mainLayer::mainMenuType::EMainMenuType uiMainMenuType);

	CMainLayer*				getMainLayer(void) { return m_pMainLayer; }

	CIMGEditor*				getIMGEditor(void) { return m_pIMGEditor; }

private:
	void					initWindow(void);
	void					initLayers(void);

	void					initMainLayer(void);
	void					initMainMenuLayers(void);
	void					initSettingsMenuLayer(void);
	void					initEditors(void);

public:
	CMainLayer*				m_pMainLayer;
	CIMGEditor*				m_pIMGEditor;

private:
	imgf::mainLayer::mainMenuType::EMainMenuType		m_uiMainMenuType;
};