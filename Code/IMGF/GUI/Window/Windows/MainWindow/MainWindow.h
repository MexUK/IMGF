#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Window/Window.h"
#include "GUI/Layer/Layers/DumpWindow/DumpWindowResult.h"
#include "GUI/Editor/Editors/DATEditor.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "GUI/Editor/Editors/ItemDefinitionEditor.h"
#include "GUI/Editor/Editors/ItemPlacementEditor.h"
#include "GUI/Editor/Editors/ModelEditor.h"
#include "GUI/Editor/Editors/CollisionEditor.h"
#include "GUI/Editor/Editors/TextureEditor.h"
#include "GUI/Editor/Editors/AnimationEditor.h"
#include "GUI/Editor/Editors/RadarEditor.h"
#include "GUI/Editor/Editors/MapEditor.h"
#include <string>
#include <vector>

class bxgx::ProgressBar;
class bxgx::TabBar;
class bxgx::Button;
class bxgx::Menu;

class imgf::MainLayer;

class imgf::MainWindow : public bxgx::Window
{
public:
	MainWindow(void);

	void						init(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						setMainMenuType(imgf::mainLayer::mainMenuType::EMainMenuType uiMainMenuType);

	MainLayer*					getMainLayer(void) { return m_pMainLayer; }
	MainLayerNoTabsOpen*		getMainLayerNoTabsOpen(void) { return m_pMainLayerNoTabsOpen; }
	bxgx::Layer*				getBlankLayer(void) { return getLayerById(99); }
	
	DATEditor*					getDATEditor(void) { return m_pDATEditor; }
	IMGEditor*					getIMGEditor(void) { return m_pIMGEditor; }
	ItemDefinitionEditor*		getItemDefinitionEditor(void) { return m_pItemDefinitionEditor; }
	ItemPlacementEditor*		getItemPlacementEditor(void) { return m_pItemPlacementEditor; }
	ModelEditor*				getModelEditor(void) { return m_pModelEditor; }
	CollisionEditor*			getCollisionEditor(void) { return m_pCollisionEditor; }
	TextureEditor*				getTextureEditor(void) { return m_pTextureEditor; }
//	TextEditor*					getTextEditor(vold) { return m_pTextEditor; }
	AnimationEditor*			getAnimationEditor(void) { return m_pAnimationEditor; }
	RadarEditor*				getRadarEditor(void) { return m_pRadarEditor; }

	void						setActiveEditor(Editor *pActiveEditor);
	Editor*						getActiveEditor(void) { return m_pActiveEditor; }

	bxcf::VectorPool<imgf::Editor*>&	getEditors(void) { return m_vecEditors; }

	Editor*						getEditorFromFileExtension(std::string& strFileExtension);
	int32						getEditorIndex(Editor *pEditor);

	bxgx::ProgressBar*			getProgressBar(void);

	void						onResizeWindow(bxcf::Vec2i& vecSizeDifference);
	void						onDropEntries(void *m_pEditorTab, std::vector<std::string> vecFileNames, std::vector<std::string> vecFileDatas);

	void						reloadLayers(void);

	void						setOpenLastFilename(std::string strFileName);
	void						clearOpenLastFilename(void);

	void						setCertainMenuItemsEnabled(bool bEnabled);
	
private:
	void						initWindow(void);
	void						initLayers(void);

	void						initSettingsMenuLayer(void);
	void						initEditors(void);
	void						initMenuRelatedItems(void);

	template <class T>
	T*							addEditor(void);
	void						addEditor(imgf::Editor *pEditor);

public:
	MainLayer*					m_pMainLayer;
	MainLayerNoTabsOpen*		m_pMainLayerNoTabsOpen;

	DATEditor*					m_pDATEditor;
	IMGEditor*					m_pIMGEditor;
	ItemDefinitionEditor*		m_pItemDefinitionEditor;
	ItemPlacementEditor*		m_pItemPlacementEditor;
	ModelEditor*				m_pModelEditor;
	CollisionEditor*			m_pCollisionEditor;
	TextureEditor*				m_pTextureEditor;
//	TextEditor*                 m_TextEditor;
	AnimationEditor*			m_pAnimationEditor;
	RadarEditor*				m_pRadarEditor;
	RadarEditor*				m_pWaterEditor;
	RadarEditor*				m_pPathsEditor;
	RadarEditor*				m_pPaintEditor;
	RadarEditor*				m_pZonsEditor;
	MapEditor*					m_pMapEditor;

	bxgx::Menu*					m_pFormatsMenu;
	bxgx::Menu*					m_pSettingsMenu;
	DumpWindowResult			m_dumpWindowResult;
	Editor*						m_pActiveEditor;
	bool						m_bDragDropOutIsOccurring;

	bxgx::Menu*					m_pRecentlyOpenMenu;
	bxgx::Menu*					m_pFileGroupMenu;

	bxgx::Button*				m_pSettingsButton;
	bxgx::Line*					m_pSettingsButtonLine1;
	bxgx::Line*					m_pSettingsButtonLine2;
	bxgx::Line*					m_pSettingsButtonLine3;

private:
	imgf::mainLayer::mainMenuType::EMainMenuType	m_uiMainMenuType;
	bxcf::VectorPool<imgf::Editor*>					m_vecEditors;
};

template <class T>
T*								imgf::MainWindow::addEditor(void)
{
	//T *pEditor = addLayer<T>(-1, false, 0);
	T *pEditor = new T;
	//pEditor->setWindow(this);
	pEditor->setMainWindow(this);
	pEditor->init();
	addEditor(pEditor);
	return pEditor;
}