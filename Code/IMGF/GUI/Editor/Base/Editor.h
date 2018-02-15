#pragma once

#include "nsbxcf.h"
#include "nsbxgx.h"
#include "nsbxgi.h"
#include "nsimgf.h"
#include "Layer/Layer.h"
#include "Pool/VectorPool.h"
#include "GUI/Editor/Base/EEditor.h"
#include "Event/EventBindable.h"
#include "Task/Tasks/Tasks.h"
#include "Static/Path.h"
#include "Window/Window.h"
#include <string>
#include <vector>

class bxgx::TabBar;
class bxgx::TextBox;

class imgf::Editor : public bxcf::EventBindable
{
public:
	Editor(EEditor uiEditorType);

	virtual void						init(void);

	virtual void						bindEvents(void);
	virtual void	 					unbindEvents(void);

	virtual void						storeControls(void);

	virtual imgf::EditorTab*					addEditorTab(std::string& strFilePath) = 0;
	virtual imgf::EditorTab*					addBlankEditorTab(std::string& strFilePath) = 0;
	template <class FormatType, class EditorTabType>
	EditorTabType*						_addEditorTab(std::string& strFilePath, bool bNewFile);
	void								removeEditorTab(EditorTab *pEditorTab);
	void								removeEditorTab2(EditorTab *pEditorTab);
	void								removeActiveEditorTab(void);

	EEditor								getEditorType(void) { return m_uiEditorType; }

	bxcf::VectorPool<EditorTab*>&		getEditorTabs(void) { return m_vecEditorTabs; }

	void								setEditorFileFormats(std::vector<std::string> vecEditorFileFormats) { m_vecEditorFileFormats = vecEditorFileFormats; }
	std::vector<std::string>&			getEditorFileFormats(void) { return m_vecEditorFileFormats; }

	void								setImportEditorFileFormats(std::vector<std::string> vecImportEditorFileFormats) { m_vecImportEditorFileFormats = vecImportEditorFileFormats; }
	std::vector<std::string>&			getImportEditorFileFormats(void) { return m_vecImportEditorFileFormats; }
	bool								isFileExtensionImportable(std::string& strFileExtension);

	void								setMainWindow(MainWindow *pMainWindow) { m_pMainWindow = pMainWindow; }
	MainWindow*							getMainWindow(void) { return m_pMainWindow; }

	void								setActiveEditorTab(EditorTab *pEditorTab);
	EditorTab*							getActiveEditorTab(void) { return m_pActiveEditorTab; }

	void								setTabBar(bxgx::TabBar *pTabBar) { m_pTabBar = pTabBar; }
	bxgx::TabBar*						getTabBar(void) { return m_pTabBar; }

	void								updateActiveFileDisplayedInfo(void);

	bool								isFilePathOpen(std::string& strFilePath);
	EditorTab*							getEditorTabByFilePath(std::string& strFilePath);

	virtual std::string					getResolvedFilePath(std::string& strFilePath) { return strFilePath; } // file name or file path

	static std::string					getEditorName(EEditor uiEditor);

	void								setEditorFileType(bxcf::fileType::EFileType uiEditorFileType) { m_uiEditorFileType = uiEditorFileType; }
	bxcf::fileType::EFileType			getEditorFileType(void) { return m_uiEditorFileType; }

	std::vector<std::string>			getFileFormatsForChooseFile(void);

	static imgf::mainLayer::input::EInputItem			getFileExtensionNewTask(std::string& strEditorFileExtension);

	void								onDragEntriesOver(bxcf::Vec2i vecCursorPosition);

	bxgx::Button*						getEditorButton(void) { return m_pEditorButton; }

	bxgx::Layer*						getLayer(void) { return m_pLayer; }

protected:
	EEditor								m_uiEditorType;
	MainWindow*							m_pMainWindow;
	EditorTab*							m_pActiveEditorTab;
	bxgx::TabBar*						m_pTabBar;
	bxcf::fileType::EFileType			m_uiEditorFileType;
	bxgx::Button*						m_pEditorButton;
	bxgx::Layer*						m_pLayer;
	std::vector<std::string>			m_vecEditorFileFormats;
	std::vector<std::string>			m_vecImportEditorFileFormats;
	bxcf::VectorPool<imgf::EditorTab*>	m_vecEditorTabs;
};

// add editor tab
template <class FormatType, class EditorTabType>
EditorTabType*							imgf::Editor::_addEditorTab(std::string& strFilePath, bool bNewFile)
{
	// check if file path is already open
	if (isFilePathOpen(strFilePath))
	{
		setActiveEditorTab(getEditorTabByFilePath(strFilePath));
		return nullptr;
	}

	// unserialize file
	FormatType *pFormat = new FormatType;
	pFormat->setFilePath(strFilePath);
	if(!bNewFile && !pFormat->readMetaData())
	{
		std::string strFileExtension = bxcf::Path::getFileExtension(strFilePath);
		imgf::Tasks::showMessage("Failed to read meta data.\r\n\r\n" + strFilePath, "Can't Open " + strFileExtension + " File");
		return nullptr;
	}

	/*
	todo
	// disable other layers
	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->getBaseLayer()->setEnabled(false);
		m_pActiveEditorTab->getLayer()->setEnabled(false);
	}
	*/

	// add editor tab
	//EditorTabType *pEditorTab = m_pMainWindow->addLayer<EditorTabType>(-1, true, -50);
	EditorTabType *pEditorTab = new EditorTabType;
	m_vecEditorTabs.addEntry(pEditorTab);

	// initialize editor tab
	pEditorTab->setEditor(this);
	pEditorTab->setFile(pFormat);

	// set active editor
	m_pMainWindow->setActiveEditor(this);

	// return editor tab
	return pEditorTab;
}