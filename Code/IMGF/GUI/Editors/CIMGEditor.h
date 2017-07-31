#ifndef CIMGEditor_H
#define CIMGEditor_H

#include "Type/Types.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "GUI/Editor/CEditor.h"
#include "Format/RockstarGames/IMG/eIMGVersion.h"
#include <string>

class CSearchEntry;
class CListControl;
class CProgressControl;
class CEditControl;
class CDropControl;
class bxcf::CIMGEntry;

class CIMGEditor : public CEditor
{
public:
	CIMGEditor(void) :
		m_uiSelectedEntryCount(0),
		m_uiSearchHitCount(0), // todo - rename to SearchHitEntryCount
		m_uiSearchFileCount(0), // todo - rename to SearchHitFileCount
		m_pEntryListControl(nullptr)
	{}

	void						initEditor(void);
	void						initMenu(void);
	void						loadRightClickMenu(int xPos, int yPos);
	void						render(void);

	void						repositionAndResizeControls(void);

	CIMGEditorTab*				addTab(std::string strIMGPath, bxcf::eIMGVersion eIMGVersionValue);
	CIMGEditorTab*				addBlankTab(std::string strIMGPath, bxcf::eIMGVersion eIMGVersionValue);
	void						removeTab(CEditorTab *pEditorTab);

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

	void						setSelectedEntryCount(uint32 uiSelectedEntryCount) { m_uiSelectedEntryCount = uiSelectedEntryCount; }
	uint32						getSelectedEntryCount(void) { return m_uiSelectedEntryCount; }

	void						setSearchHitCount(uint32 uiSearchHitCount) { m_uiSearchHitCount = uiSearchHitCount; }
	uint32						getSearchHitCount(void) { return m_uiSearchHitCount; }

	void						setSearchFileCount(uint32 uiSearchFileCount) { m_uiSearchFileCount = uiSearchFileCount; }
	uint32						getSearchFileCount(void) { return m_uiSearchFileCount; }

	void						setEntryListControl(CListControl *pEntryListControl) { m_pEntryListControl = pEntryListControl; }
	CListControl*				getEntryListControl(void) { return m_pEntryListControl; }

	std::vector<CSearchEntry*>&	getSearchEntries(void) { return m_vecSearchEntries; }

private:
	CIMGEditorTab*				_addTab(bxcf::CIMGFormat *pIMGFormat);

private:
	uint32						m_uiSelectedEntryCount;
	uint32						m_uiSearchHitCount;
	uint32						m_uiSearchFileCount;
	CListControl*				m_pEntryListControl;
	CProgressControl*			m_pProgressBar;
	CEditControl*				m_pSearchBox;
	CDropControl*				m_pEntryTypeFilter;
	CDropControl*				m_pEntryVersionFilter;
	std::vector<CSearchEntry*>	m_vecSearchEntries;
};

#endif