#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "GUI/Editor/Editors/Tab/IMGEditorTab.h"
#include "GUI/Editor/Base/Editor.h"
#include "Format/IMG/Regular/EIMGVersion.h"
#include <string>

class imgf::MainWindow;
class imgf::SearchEntry;
class bxgx::Grid;
class bxgx::TextBox;
class bxgx::DropDown;
class bxgi::IMGEntry;
class bxgi::IMGFormat;

class imgf::IMGEditor : public Editor
{
public:
	IMGEditor(void);

	void						init(void);
	void						render(void);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);
	
	IMGEditorTab*				addFile(std::string& strFilePath);
	IMGEditorTab*				addBlankFile(std::string strIMGPath, bxgi::EIMGVersion EIMGVersionValue);
	IMGEditorTab*				addTabObjectAndTabControl(bxgi::IMGFormat *img, bool bNewFile);

	void						removeFile(IMGEditorTab *pIMGEditorFile);
	void						removeActiveFile(void);

	void						setFileInfoText(EditorTab *pEditorFile);
	void						clearFileInfoText(void);
	
	bxcf::VectorPool<IMGEditorTab*>&	getIMGTabs(void) { return (bxcf::VectorPool<IMGEditorTab*>&)m_vecTabs; }





	void						removeTab(IMGEditorTab *pEditorTab) {}

	void						refreshActiveTab(void);
	IMGEditorTab*				getActiveTab(void) { return (IMGEditorTab*) Editor::getActiveFile(); }
	void						setActiveTab(IMGEditorTab *pActiveTab);

	void						readdColumnsToMainListView(bxgi::EIMGVersion EIMGVersionValue);
	void						addColumnsToMainListView(bxgi::EIMGVersion EIMGVersionValue);
	void						removeColumnsFromMainListView(void);
	int							getMainListControlItemByEntry(bxgi::IMGEntry *pIMGEntry); // todo - naming -- list control vs list view

	void						onSelectIMGEntry(bool bEntryIsSelected);

	void						logAllTabs(std::string strText, bool bExtendedModeOnly = false);
	void						logWithNoTabsOpen(std::string strText, bool bExtendedModeOnly = false);

	uint32						getEntryCountForAllTabs(void);
	void						updateSelectedEntryCountText(void);

	std::vector<bxgi::IMGFormat*>	getAllMainWindowTabsIMGFiles(void);

	void						setMainWindow(MainWindow *pMainWindow) { m_pMainWindow = pMainWindow; }
	MainWindow*					getMainWindow(void) { return m_pMainWindow; }

	void						setSelectedEntryCount(uint32 uiSelectedEntryCount) { m_uiSelectedEntryCount = uiSelectedEntryCount; }
	uint32						getSelectedEntryCount(void) { return m_uiSelectedEntryCount; }

	void						setSearchHitCount(uint32 uiSearchHitCount) { m_uiSearchHitCount = uiSearchHitCount; }
	uint32						getSearchHitCount(void) { return m_uiSearchHitCount; }

	void						setSearchFileCount(uint32 uiSearchFileCount) { m_uiSearchFileCount = uiSearchFileCount; }
	uint32						getSearchFileCount(void) { return m_uiSearchFileCount; }

	void						setEntryGrid(bxgx::Grid *pEntryGrid) { m_pEntryGrid = pEntryGrid; }
	bxgx::Grid*					getEntryGrid(void) { return m_pEntryGrid; }

	std::vector<SearchEntry*>&	getSearchEntries(void) { return m_vecSearchEntries; }

	std::string					getResolvedFilePath(std::string& strFilePath);

private:
	void						addControls(void);
	void						initControls(void);

	void						initMenu(void);
	void						loadRightClickMenu(int xPos, int yPos);
	
	IMGEditorTab*				_addTab(bxgi::IMGFormat *pIMGFormat);

public:
	bxgx::Grid*					m_pEntryGrid;
	bxgx::DropDown*				m_pEntryTypeFilter;
	bxgx::DropDown*				m_pEntryVersionFilter;

private:
	MainWindow*					m_pMainWindow;
	uint32						m_uiSelectedEntryCount;
	uint32						m_uiSearchHitCount;
	uint32						m_uiSearchFileCount;
	std::vector<SearchEntry*>	m_vecSearchEntries;
};