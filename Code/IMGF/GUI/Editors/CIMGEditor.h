#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "GUI/Editor/CEditor.h"
#include "Format/IMG/Regular/EIMGVersion.h"
#include "Event/Events.h"
#include <string>

class imgf::CMainWindow;
class imgf::CSearchEntry;
class bxgx::CGrid;
class bxgx::CTextBox;
class bxgx::CDropDown;
class bxgi::CIMGEntry;
class bxgi::CIMGFormat;

class imgf::CIMGEditor : public CEditor, public bxcf::EventBindable
{
public:
	CIMGEditor(void);

	void						init(void);
	void						render(void);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	static bool					validateFile(bxgi::CIMGFormat *img);

	CIMGEditorTab*				addFile(bxgi::CIMGFormat *img);
	CIMGEditorTab*				addBlankFile(std::string strIMGPath, bxgi::EIMGVersion EIMGVersionValue);
	CIMGEditorTab*				addTabObjectAndTabControl(bxgi::CIMGFormat *img);
	void						removeFile(CIMGEditorTab *pIMGEditorFile);
	void						removeActiveFile(void);
	
	void						onUnserializeEntry(bxgi::CIMGFormat *img);
	void						onTaskProgress(void);

	void						setFileInfoText(CEditorTab *pEditorFile);
	void						clearFileInfoText(void);





	void						removeTab(CIMGEditorTab *pEditorTab) {}

	void						refreshActiveTab(void);
	CIMGEditorTab*				getActiveTab(void) { return (CIMGEditorTab*) CEditor::getActiveFile(); }
	void						setActiveTab(CIMGEditorTab *pActiveTab);

	void						readdColumnsToMainListView(bxgi::EIMGVersion EIMGVersionValue);
	void						addColumnsToMainListView(bxgi::EIMGVersion EIMGVersionValue);
	void						removeColumnsFromMainListView(void);
	int							getMainListControlItemByEntry(bxgi::CIMGEntry *pIMGEntry); // todo - naming -- list control vs list view

	void						onSelectIMGEntry(bool bEntryIsSelected);

	void						logAllTabs(std::string strText, bool bExtendedModeOnly = false);
	void						logWithNoTabsOpen(std::string strText, bool bExtendedModeOnly = false);

	uint32						getEntryCountForAllTabs(void);
	void						updateSelectedEntryCountText(void);

	std::vector<bxgi::CIMGFormat*>	getAllMainWindowTabsIMGFiles(void);

	void						setMainWindow(CMainWindow *pMainWindow) { m_pMainWindow = pMainWindow; }
	CMainWindow*				getMainWindow(void) { return m_pMainWindow; }

	void						setSelectedEntryCount(uint32 uiSelectedEntryCount) { m_uiSelectedEntryCount = uiSelectedEntryCount; }
	uint32						getSelectedEntryCount(void) { return m_uiSelectedEntryCount; }

	void						setSearchHitCount(uint32 uiSearchHitCount) { m_uiSearchHitCount = uiSearchHitCount; }
	uint32						getSearchHitCount(void) { return m_uiSearchHitCount; }

	void						setSearchFileCount(uint32 uiSearchFileCount) { m_uiSearchFileCount = uiSearchFileCount; }
	uint32						getSearchFileCount(void) { return m_uiSearchFileCount; }

	void						setEntryGrid(bxgx::CGrid *pEntryGrid) { m_pEntryGrid = pEntryGrid; }
	bxgx::CGrid*			getEntryGrid(void) { return m_pEntryGrid; }

	std::vector<CSearchEntry*>&	getSearchEntries(void) { return m_vecSearchEntries; }

	std::string					getResolvedFilePath(std::string& strFilePath);

private:
	void						addControls(void);
	void						initControls(void);

	void						initMenu(void);
	void						loadRightClickMenu(int xPos, int yPos);
	
	CIMGEditorTab*				_addTab(bxgi::CIMGFormat *pIMGFormat);

public:
	bxgx::CGrid*			m_pEntryGrid;
	bxgx::CTextBox*		m_pLog;
	bxgx::CDropDown*			m_pEntryTypeFilter;
	bxgx::CDropDown*			m_pEntryVersionFilter;

private:
	CMainWindow*				m_pMainWindow;
	uint32						m_uiSelectedEntryCount;
	uint32						m_uiSearchHitCount;
	uint32						m_uiSearchFileCount;
	std::vector<CSearchEntry*>	m_vecSearchEntries;
};