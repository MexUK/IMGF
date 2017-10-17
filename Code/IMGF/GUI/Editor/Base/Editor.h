#pragma once

#include "nsimgf.h"
#include "Layer/Layer.h"
#include "Pool/VectorPool.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "Event/EventBindable.h"
#include <string>

class bxgx::TabBar;
class bxgx::TextBox;

class imgf::Editor : public bxgx::Layer, public bxcf::EventBindable
{
public:
	Editor(void);

	virtual void						init(void);

	virtual void						addControls(void);
	virtual void						initControls(void);

	template <class FormatType, class EditorTabType>
	EditorTabType*						addEditorTab(std::string& strFilePath, bool bNewFile = false);
	void								removeFile(EditorTab *pEditorTab);
	void								removeActiveFile(void);

	bxcf::VectorPool<EditorTab*>&		getTabs(void) { return m_vecTabs; }

	void								setEditorFileFormats(std::vector<std::string> vecEditorFileFormats) { m_vecEditorFileFormats = vecEditorFileFormats; }
	std::vector<std::string>&			getEditorFileFormats(void) { return m_vecEditorFileFormats; }

	void								setMainWindow(MainWindow *pMainWindow) { m_pMainWindow = pMainWindow; }
	MainWindow*							getMainWindow(void) { return m_pMainWindow; }

	void								setActiveFile(EditorTab *pEditorFile);
	EditorTab*							getActiveFile(void) { return m_pActiveFile; }

	void								setTabBar(bxgx::TabBar *pTabBar) { m_pTabBar = pTabBar; }
	bxgx::TabBar*						getTabBar(void) { return m_pTabBar; }

	void								updateActiveFileDisplayedInfo(void);

	bool								isFilePathOpen(std::string& strFilePath);
	EditorTab*							getEditorTabByFilePath(std::string& strFilePath);

	virtual std::string					getResolvedFilePath(std::string& strFilePath) { return strFilePath; } // file name or file path

protected:
	MainWindow*							m_pMainWindow;
	EditorTab*							m_pActiveFile;
	bxgx::TabBar*						m_pTabBar;
	std::vector<std::string>			m_vecEditorFileFormats;
	bxcf::VectorPool<EditorTab*>		m_vecTabs;
};

// add editor tab
template <class FormatType, class EditorTabType>
EditorTabType*							imgf::Editor::addEditorTab(std::string& strFilePath, bool bNewFile)
{
	// check if file path is already open
	if (isFilePathOpen(strFilePath))
	{
		setActiveFile(getEditorTabByFilePath(strFilePath));
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

	// add editor tab
	EditorTabType *pEditorTab = m_pWindow->addLayer<EditorTabType>(-1, true, -50);
	m_vecTabs.addEntry(pEditorTab);

	// disable other layers
	if (m_pActiveFile)
	{
		m_pActiveFile->setEnabled(false);
	}
	else
	{
		setEnabled(false);
		getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->setEnabled(false);
	}

	// initialize editor tab
	pEditorTab->setEditor(this);
	pEditorTab->setFile(pFormat);

	// return editor tab
	return pEditorTab;
}