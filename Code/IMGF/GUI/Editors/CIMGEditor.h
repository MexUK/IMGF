#ifndef CIMGEditor_H
#define CIMGEditor_H

#include "Type/Types.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "GUI/Editor/CEditor.h"
#include "Format/RockstarGames/IMG/eIMGVersion.h"
#include <string>

class CMainWindow;
class CSearchEntry;
class CGridControl;
class bxcf::CIMGEntry;
class bxcf::CIMGFormat;

class CIMGEditor : public CEditor
{
public:
	CIMGEditor(void);

	void						init(void);
	void						render(void);

	void						repositionAndResizeControls(void);

	static bool					validateFile(bxcf::CIMGFormat *img);

	CIMGEditorTab*				addFile(bxcf::CIMGFormat *img);
	CIMGEditorTab*				addBlankFile(std::string strIMGPath, bxcf::eIMGVersion eIMGVersionValue);
	void						removeTab(CEditorTab *pEditorTab);

	CIMGEditorTab*				addTab(bxcf::CIMGFormat *img);

	void						refreshActiveTab(void);
	CIMGEditorTab*				getActiveTab(void) { return (CIMGEditorTab*) CEditor::getActiveTab(); }
	void						setActiveTab(CIMGEditorTab *pActiveTab);

	void						readdColumnsToMainListView(bxcf::eIMGVersion eIMGVersionValue);
	void						addColumnsToMainListView(bxcf::eIMGVersion eIMGVersionValue);
	void						removeColumnsFromMainListView(void);
	int							getMainListControlItemByEntry(bxcf::CIMGEntry *pIMGEntry); // todo - naming -- list control vs list view

	void						onSelectIMGEntry(bool bEntryIsSelected);

	void						logAllTabs(std::string strText, bool bExtendedModeOnly = false);
	void						logWithNoTabsOpen(std::string strText, bool bExtendedModeOnly = false);

	uint32						getEntryCountForAllTabs(void);
	void						updateSelectedEntryCountText(void);

	std::vector<bxcf::CIMGFormat*>	getAllMainWindowTabsIMGFiles(void);

	void						setMainWindow(CMainWindow *pMainWindow) { m_pMainWindow = pMainWindow; }
	CMainWindow*				getMainWindow(void) { return m_pMainWindow; }

	void						setSelectedEntryCount(uint32 uiSelectedEntryCount) { m_uiSelectedEntryCount = uiSelectedEntryCount; }
	uint32						getSelectedEntryCount(void) { return m_uiSelectedEntryCount; }

	void						setSearchHitCount(uint32 uiSearchHitCount) { m_uiSearchHitCount = uiSearchHitCount; }
	uint32						getSearchHitCount(void) { return m_uiSearchHitCount; }

	void						setSearchFileCount(uint32 uiSearchFileCount) { m_uiSearchFileCount = uiSearchFileCount; }
	uint32						getSearchFileCount(void) { return m_uiSearchFileCount; }

	void						setEntryGrid(CGridControl *pEntryGrid) { m_pEntryGrid = pEntryGrid; }
	CGridControl*				getEntryGrid(void) { return m_pEntryGrid; }

	std::vector<CSearchEntry*>&	getSearchEntries(void) { return m_vecSearchEntries; }

public:
	CGridControl*				m_pEntryGrid;

private:
	void						addControls(void);
	void						initControls(void);

	void						initMenu(void);
	void						loadRightClickMenu(int xPos, int yPos);
	
	CIMGEditorTab*				_addTab(bxcf::CIMGFormat *pIMGFormat);

private:
	CMainWindow*				m_pMainWindow;
	uint32						m_uiSelectedEntryCount;
	uint32						m_uiSearchHitCount;
	uint32						m_uiSearchFileCount;
	std::vector<CSearchEntry*>	m_vecSearchEntries;
};

#endif