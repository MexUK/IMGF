#pragma once

#include "nsimgf.h"
#include "Layer/Layer.h"
#include "Pool/VectorPool.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "Event/EventBindable.h"
#include "Task/Tasks/Tasks.h"
#include <string>

class bxgx::TabBar;
class bxgx::TextBox;

class imgf::Editor : public bxgx::Layer, public bxcf::EventBindable
{
public:
	Editor(void);

	virtual void						init(void);

	virtual void						bindEvents(void);
	virtual void	 					unbindEvents(void);

	virtual void						addControls(void);
	virtual void						initControls(void);

	template <class FormatType, class EditorTabType>
	EditorTabType*						addEditorTab(std::string& strFilePath, bool bNewFile = false);
	void								removeEditorTab(EditorTab *pEditorTab);
	void								removeActiveEditorTab(void);

	bxcf::VectorPool<EditorTab*>&		getEditorTabs(void) { return m_vecEditorTabs; }

	void								setEditorFileFormats(std::vector<std::string> vecEditorFileFormats) { m_vecEditorFileFormats = vecEditorFileFormats; }
	std::vector<std::string>&			getEditorFileFormats(void) { return m_vecEditorFileFormats; }

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

protected:
	MainWindow*							m_pMainWindow;
	EditorTab*							m_pActiveEditorTab;
	bxgx::TabBar*						m_pTabBar;
	std::vector<std::string>			m_vecEditorFileFormats;
	bxcf::VectorPool<EditorTab*>		m_vecEditorTabs;
};

// add editor tab
template <class FormatType, class EditorTabType>
EditorTabType*							imgf::Editor::addEditorTab(std::string& strFilePath, bool bNewFile)
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

	// add editor tab
	EditorTabType *pEditorTab = m_pWindow->addLayer<EditorTabType>(-1, true, -50);
	m_vecEditorTabs.addEntry(pEditorTab);

	// disable other layers
	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->setEnabled(false);
	}
	else
	{
		//setEnabled(false);
		getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->setEnabled(false);
	}

	// initialize editor tab
	pEditorTab->setEditor(this);
	pEditorTab->setFile(pFormat);

	// return editor tab
	return pEditorTab;
}