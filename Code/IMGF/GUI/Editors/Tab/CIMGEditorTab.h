#pragma once

#include <Windows.h>
#include "GUI/Editor/Tab/CEditorTab.h"
#include "Format/IMG/Regular/CIMGFormat.h"
#include "Tasks/Filter/CFilterOptions.h"
#include "Event/Events.h"
#include "Task/CTaskManager.h"
#include <string>
#include <vector>

class CIMGEditor;
class bxgi::CIMGFormat;
class bxgi::CIMGEntry;
class CDBFormat;
class CListCtrl; // temp
class bxgx::CDropControlEntry;

class CIMGEditorTab : public CEditorTab, public bxcf::EventBindable
{
public:
	CIMGEditorTab(void);

	void						unload(void);

	void						init(void);

	void						addControls(void);
	void						removeControls(void);
	void						initControls(void);
	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	void						onSelectDropEntry(bxgx::CDropControlEntry *pDropEntry);

	void						setIMGEditor(CIMGEditor *pEditor) { m_pEditor = pEditor; }
	CIMGEditor*					getIMGEditor(void) { return m_pEditor; }

	void						setIMGFile(bxgi::CIMGFormat *pIMGFile) { m_pIMGFile = pIMGFile; }
	bxgi::CIMGFormat*			getIMGFile(void) { return m_pIMGFile; }






	void						setSearchText(std::string strSearchText) { m_strSearchText = strSearchText; }
	std::string					getSearchText(void) { return m_strSearchText; }

	bool						isOverwriteEntryOptionSet(void) { return getOverwriteEntryOption() != 0; }
	void						resetOverwriteEntryOption(void) { setOverwriteEntryOption(0); }
	void						setOverwriteEntryOption(uint32 uiOption) { m_uiOverwriteEntryOption = uiOption; }
	uint32						getOverwriteEntryOption(void) { return m_uiOverwriteEntryOption; }

	void						setListViewHwnd(HWND hWnd) { m_hListViewHwnd = hWnd; }
	HWND						getListViewHwnd(void) { return m_hListViewHwnd; }

	//CListCtrl*					getListView(void) { return (CListCtrl*)CWnd::FromHandle(getListViewHwnd()); } // todo
	CListCtrl*					getListView(void) { return nullptr; } // todo

	bool						isRestoringFilterOptions(void) { return m_bRestoringFilterOptions; }

	void						log(std::string strText, bool bExtendedModeOnly = false);
	void						clearLogs(void);
	std::vector<std::string>&	getLogLinesGUI(void) { return m_vecLogLinesGUI; }
	std::vector<std::string>&	getLogLinesBasic(void) { return m_vecLogLinesBasic; }
	std::vector<std::string>&	getLogLinesExtended(void) { return m_vecLogLinesExtended; }

	void						addEntryViaFile(std::string strEntryFilePath, std::string strEntryName = "");
	void						addEntryViaData(std::string strEntryName, std::string strEntryData);
	void						replaceEntryViaFile(std::string strEntryName, std::string strEntryFilePath, std::string strNewEntryName = "");
	void						replaceEntryViaData(std::string strEntryName, std::string& strEntryData, std::string strNewEntryName = "");
	void						addOrReplaceEntryViaFile(std::string strEntryFilePath, std::string strEntryName = ""); // if entry with name already exists, then it is replaced, otherwise it is added.
	void						addOrReplaceEntryViaData(std::string strEntryName, std::string strEntryData); // if entry with name already exists, then it is replaced, otherwise it is added.
	void						addOrReplaceEntryViaFileAndSettings(std::string strEntryFilePath, std::string strEntryName = ""); // entry is added or replaced depending on settings.
	void						addOrReplaceEntryViaDataAndSettings(std::string strEntryName, std::string strEntryData); // entry is added or replaced depending on settings.
	void						removeEntry(bxgi::CIMGEntry *pIMGEntry);

	void						addGridHeaders(void);
	void						addGridEntries(void);
	void						readdGridEntries(void);
	void						addGridEntry(bxgi::CIMGEntry *pIMGEntry, uint32 uiEntryIndex = -1, void **pRows = nullptr);
	void						updateGridEntry(bxgi::CIMGEntry *pIMGEntry);
	uint32						getMainListViewItemIndexByItemData(bxgi::CIMGEntry *pIMGEntry);

	bxgi::CIMGEntry*					getEntryByName(std::string strEntryName);

	void						rebuild(std::string strIMGPath = "", bool bLog = true);
	uint32						merge(std::string strPath, std::vector<std::string>& vecImportedEntryNames);
	void						splitSelectedEntries(std::string strPath, bxgi::eIMGVersion eIMGVersion, bool bDeleteFromSource, std::vector<std::string>& vecSplitEntryNames);
	void						replace(std::vector<std::string>& vecPaths, std::vector<std::string>& vecReplacedEntryNames);
	void						searchText(void);

	void						setIMGModifiedSinceRebuild(bool bState) { m_bIMGModifiedSinceRebuild = bState; }
	bool						getIMGModifiedSinceRebuild(void) { return m_bIMGModifiedSinceRebuild; } // todo - rename to has..Been.. instead of get

	void						updateEntryCountText(void);
	void						updateIMGText(void);

	void						storeFilterOptions(void);
	void						restoreFilterOptions(void);
	bool						isFilterActive(void);
	
	void						sortEntries(void);
	
	void						onEntryChange(bxgi::CIMGEntry *pIMGEntry);
	void						loadProtectedEntryStates(void);

	void						loadFilter_Type(void);
	void						loadFilter_Version(void);
	void						unloadFilter_Type(void);
	void						unloadFilter_Version(void);

	void						reassignEntryIds(void);

	std::vector<bxgi::CIMGEntry*>		getSelectedEntries(void);

	void						setActiveFilter(std::string strFilterName, std::string strValue) { m_umapActiveFilterValues[strFilterName] = strValue; }
	std::string					getActiveFilter(std::string strFilterName) { return m_umapActiveFilterValues[strFilterName]; }

	void						checkToApplyCompression(bxgi::CIMGEntry *pIMGEntry);

	void						checkForUnknownRWVersionEntries(void);

	CDBFormat*					m_pDBFile; // todo - make private

private:
	void						loadProtectedEntryState(bxgi::CIMGEntry *pIMGEntry);

private:
	CIMGEditor*					m_pEditor;

	bxgx::CGridControl*			m_pEntryGrid;
	bxgx::CTextBoxControl*		m_pLog;
	bxgx::CDropControl*			m_pEntryTypeFilter;
	bxgx::CDropControl*			m_pEntryVersionFilter;

	bxgi::CIMGFormat*			m_pIMGFile;
	std::vector<std::string>	m_vecLogLinesGUI;
	std::vector<std::string>	m_vecLogLinesBasic;
	std::vector<std::string>	m_vecLogLinesExtended;
	std::string					m_strSearchText;
	CFilterOptions				m_filterOptions;
	bool						m_bRestoringFilterOptions;
	HWND						m_hListViewHwnd;
	bool						m_bIMGModifiedSinceRebuild;
	std::unordered_map<std::string, std::string>	m_umapActiveFilterValues;
	uint32						m_uiOverwriteEntryOption;
};