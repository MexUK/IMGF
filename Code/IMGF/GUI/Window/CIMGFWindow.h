#pragma once

#include "imgf.h"
#include "Window/CWindow.h"
#include <string>
#include <vector>

class CMainLayer;
class CEditor;
class CIMGEditor;

class CIMGFWindow : public CWindow
{
public:
	CIMGFWindow(void);

	void					init(void);

	void					setMainMenuType(imgf::mainLayer::mainMenuType::EMainMenuType uiMainMenuType);

private:
	void					initWindow(void);
	void					initLayers(void);

	void					initMainLayer(void);
	void					initMainMenuLayers(void);
	void					initEditors(void);

public:
	CMainLayer*				m_pMainLayer;
	CIMGEditor*				m_pIMGEditor;

private:
	imgf::mainLayer::mainMenuType::EMainMenuType		m_uiMainMenuType;
};