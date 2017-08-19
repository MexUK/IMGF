#ifndef CIMGEditor_H
#define CIMGEditor_H

#include "Type/Types.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "GUI/Editor/CEditor.h"
#include "Format/IMG/Regular/eIMGVersion.h"
#include "Event/Events.h"
#include <string>

class CMainWindow;
class CSearchEntry;
class CGridControl;
class CTextBoxControl;
class CDropControl;
class bxgi::CIMGEntry;
class bxgi::CIMGFormat;

class CIMGEditor : public CEditor
{
public:
	CIMGEditor(void);

	void						init(void);
	void						render(void);

	void						repositionAndResizeControls(void);

	static bool					validateFile(bxgi::CIMGFormat *img);

	CIMGEditorTab*				addFile(bxgi::CIMGFormat *img);
	CIMGEditorTab*				addBlankFile(std::string strIMGPath, bxgi::eIMGVersion eIMGVersionValue);
	CIMGEditorTab*				addTabObjectAndTabControl(bxgi::CIMGFormat *img);
	void						removeFile(CIMGEditorTab *pIMGEditorFile);
	void						removeActiveFile(void);

	void						setFileInfoText(CEditorTab *pEditorFile);
	void						clearFileInfoText(void);





	void						removeTab(CIMGEditorTab *pEditorTab) {}

	void						refreshActiveTab(void);
	CIMGEditorTab*				getActiveTab(void) { return (CIMGEditorTab*) CEditor::getActiveFile(); }
	void						setActiveTab(CIMGEditorTab *pActiveTab);

	void						readdColumnsToMainListView(bxgi::eIMGVersion eIMGVersionValue);
	void						addColumnsToMainListView(bxgi::eIMGVersion eIMGVersionValue);
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

	void						setEntryGrid(CGridControl *pEntryGrid) { m_pEntryGrid = pEntryGrid; }
	CGridControl*				getEntryGrid(void) { return m_pEntryGrid; }

	std::vector<CSearchEntry*>&	getSearchEntries(void) { return m_vecSearchEntries; }

private:
	void						addControls(void);
	void						initControls(void);

	void						initMenu(void);
	void						loadRightClickMenu(int xPos, int yPos);
	
	CIMGEditorTab*				_addTab(bxgi::CIMGFormat *pIMGFormat);

public:
	CGridControl*				m_pEntryGrid;
	CTextBoxControl*			m_pLog;
	CDropControl*				m_pEntryTypeFilter;
	CDropControl*				m_pEntryVersionFilter;

private:
	CMainWindow*				m_pMainWindow;
	uint32						m_uiSelectedEntryCount;
	uint32						m_uiSearchHitCount;
	uint32						m_uiSearchFileCount;
	std::vector<CSearchEntry*>	m_vecSearchEntries;
};

#endif