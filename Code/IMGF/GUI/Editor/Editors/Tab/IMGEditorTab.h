#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Task/Tasks/Filter/FilterOptions.h"
#include "Task/TaskManager.h"
#include <string>
#include <vector>
#include <Windows.h>

class imgf::IMGEditor;
class bxgi::IMGFormat;
class bxgi::IMGEntry;
class imgf::DBFormat;
class bxgx::DropDownItem;
class bxgx::Grid;
class bxgi::IMGFormat;

class imgf::IMGEditorTab : public imgf::EditorTab
{
public:
	IMGEditorTab(void);
	~IMGEditorTab(void);

	void						unload(void);

	void						init(void);

	void						onFileLoaded(void);

	void						addControls(void);
	void						removeControls(void);
	void						initControls(void);
	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	bool						unserializeFile(void);

	void						onUnserializeEntry(bxgi::IMGFormat *img);

	void						onSelectDropEntry(bxgx::DropDownItem *pDropEntry);
	void						onChangeTextBox(bxgx::TextBox *pTextBox);

	void						setIMGEditor(IMGEditor *pEditor) { m_pEditor = pEditor; }
	IMGEditor*					getIMGEditor(void) { return m_pEditor; }

	void						setIMGFile(bxgi::IMGFormat *pIMGFile) { m_pIMGFile = pIMGFile; }
	bxgi::IMGFormat*			getIMGFile(void) { return m_pIMGFile; }

	void						setTabMarkedForClose(bool bTabMarkedForClose) { m_bTabMarkedForClose = bTabMarkedForClose; }
	bool						isTabMarkedForClose(void) { return m_bTabMarkedForClose; }

	void						setTabReadyToClose(bool bTabReadyToClose) { m_bTabReadyToClose = bTabReadyToClose; }
	bool						isTabReadyToClose(void) { return m_bTabReadyToClose; }

	//void						setEntryGrid(bxgx::Grid *pEntryGrid) { m_pEntryGrid = pEntryGrid; } // todo - still needed?
	bxgx::Grid*					getEntryGrid(void) { return m_pEntryGrid; }
	bxgx::DropDown*				getEntryTypeFilter(void) { return m_pEntryTypeFilter; }
	bxgx::DropDown*				getEntryVersionFilter(void) { return m_pEntryVersionFilter; }







	void						setSearchText(std::string strSearchText) { m_strSearchText = strSearchText; }
	std::string					getSearchText(void) { return m_strSearchText; }

	bool						isOverwriteEntryOptionSet(void) { return getOverwriteEntryOption() != 0; }
	void						resetOverwriteEntryOption(void) { setOverwriteEntryOption(0); }
	void						setOverwriteEntryOption(uint32 uiOption) { m_uiOverwriteEntryOption = uiOption; }
	uint32						getOverwriteEntryOption(void) { return m_uiOverwriteEntryOption; }

	void						setListViewHwnd(HWND hWnd) { m_hListViewHwnd = hWnd; }
	HWND						getListViewHwnd(void) { return m_hListViewHwnd; }

	//CListCtrl*					getListView(void) { return (CListCtrl*)CWnd::FromHandle(getListViewHwnd()); } // todo
	//CListCtrl*					getListView(void) { return nullptr; } // todo

	bool						isRestoringFilterOptions(void) { return m_bRestoringFilterOptions; }

	//void						log(std::string strText, bool bExtendedModeOnly = false);
	void						clearLogs(void);
	std::vector<std::string>&	getLogLinesGUI(void) { return m_vecLogLinesGUI; }
	std::vector<std::string>&	getLogLinesBasic(void) { return m_vecLogLinesBasic; }
	std::vector<std::string>&	getLogLinesExtended(void) { return m_vecLogLinesExtended; }

	void						addFile(std::string strEntryFilePath, std::string strEntryName = "");
	void						addEntryViaData(std::string strEntryName, std::string strEntryData);
	void						replaceEntryViaFile(std::string strEntryName, std::string strEntryFilePath, std::string strNewEntryName = "");
	void						replaceEntryViaData(std::string strEntryName, std::string& strEntryData, std::string strNewEntryName = "");
	void						addOrReplaceEntryViaFile(std::string strEntryFilePath, std::string strEntryName = ""); // if entry with name already exists, then it is replaced, otherwise it is added.
	void						addOrReplaceEntryViaData(std::string strEntryName, std::string strEntryData); // if entry with name already exists, then it is replaced, otherwise it is added.
	void						addOrReplaceEntryViaFileAndSettings(std::string strEntryFilePath, std::string strEntryName = ""); // entry is added or replaced depending on settings.
	void						addOrReplaceEntryViaDataAndSettings(std::string strEntryName, std::string strEntryData); // entry is added or replaced depending on settings.
	void						removeEntry(bxgi::IMGEntry *pIMGEntry);
	void						removeAllEntries(void);

	void						addGridHeaders(void);
	void						addGridEntries(void);
	void						readdGridEntries(void);
	void						addGridEntry(bxgi::IMGEntry *pIMGEntry, uint32 uiEntryIndex = -1, void **pRows = nullptr);
	void						updateGridEntry(bxgi::IMGEntry *pIMGEntry);
	uint32						getMainListViewItemIndexByItemData(bxgi::IMGEntry *pIMGEntry);

	bxgi::IMGEntry*					getEntryByName(std::string strEntryName);
	std::vector<bxgi::IMGEntry*>	getEntriesByNumericMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, uint32 uiValue1, uint32 uiValue2);
	std::vector<bxgi::IMGEntry*>	getEntriesByStringMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, std::string& strValue1, std::string& strValue2, bool bMatchWildcard);

	void						rebuild(std::string strIMGPath = "", bool bLog = true);
	uint32						merge(std::string strPath, std::vector<std::string>& vecImportedEntryNames);
	void						splitSelectedEntries(std::string strPath, bxgi::EIMGVersion EIMGVersion, bool bDeleteFromSource, std::vector<std::string>& vecSplitEntryNames);
	void						replace(std::vector<std::string>& vecPaths, std::vector<std::string>& vecReplacedEntryNames);
	void						searchText(void);

	void						setIMGModifiedSinceRebuild(bool bState) { m_bIMGModifiedSinceRebuild = bState; }
	bool						getIMGModifiedSinceRebuild(void) { return m_bIMGModifiedSinceRebuild; } // todo - rename to has..Been.. instead of get

	void						updateEntryCountText(void);
	void						updateTabText(void);
	void						updateIMGText(void);

	void						storeFilterOptions(void);
	void						restoreFilterOptions(void);
	bool						isFilterActive(void);
	
	void						sortEntries(void);
	
	void						onEntryChange(bxgi::IMGEntry *pIMGEntry);
	void						loadProtectedEntryStates(void);

	void						loadFilter_Type(void);
	void						loadFilter_Version(void);
	void						unloadFilter_Type(void);
	void						unloadFilter_Version(void);

	void						reassignEntryIds(void);

	std::vector<bxgi::IMGEntry*>	getSelectedEntries(void);

	void						setActiveFilter(std::string strFilterName, std::string strValue) { m_umapActiveFilterValues[strFilterName] = strValue; }
	std::string					getActiveFilter(std::string strFilterName) { return m_umapActiveFilterValues[strFilterName]; }

	void						checkToApplyCompression(bxgi::IMGEntry *pIMGEntry);

	void						checkForUnknownRWVersionEntries(void);

	DBFormat*					m_pDBFile; // todo - make private

private:
	void						loadProtectedEntryState(bxgi::IMGEntry *pIMGEntry);

private:
	IMGEditor*					m_pEditor;

	bxgx::Grid*					m_pEntryGrid;
	bxgx::DropDown*				m_pEntryTypeFilter;
	bxgx::DropDown*				m_pEntryVersionFilter;
	bool						m_bTabMarkedForClose;
	bool						m_bTabReadyToClose;

	bxgi::IMGFormat*			m_pIMGFile;
	std::string					m_strSearchText;
	FilterOptions				m_filterOptions;
	bool						m_bRestoringFilterOptions;
	HWND						m_hListViewHwnd;
	bool						m_bIMGModifiedSinceRebuild;
	uint32						m_uiOverwriteEntryOption;
	std::unordered_map<std::string, std::string>	m_umapActiveFilterValues;
	std::vector<std::string>	m_vecLogLinesGUI;
	std::vector<std::string>	m_vecLogLinesBasic;
	std::vector<std::string>	m_vecLogLinesExtended;
};