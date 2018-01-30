#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Pool/VectorPool.h"
#include "Event/EventBindable.h"
#include "Event/EInputEvent.h"
#include "../BXCF/Event/EEvent.h"
#include "Format/ContainerFormat.h"
#include "Format/FormatEntry.h"
#include <string>
#include <vector>
#include <thread>

class imgf::Editor;
class bxcf::Format;
class bxgx::Tab;
class bxgx::TextBox;
class bxgx::ProgressBar;

class imgf::EditorTab : public bxcf::EventBindable
{
public:
	EditorTab(void);
	virtual ~EditorTab(void);

	virtual bool						init(bool bIsNewFile);

	virtual void						bindEvents(void);
	virtual void						unbindEvents(void);

	virtual void						initLayer(void) {}

	virtual bool						unserializeFile(void) = 0;
	virtual void						onFileLoaded(void) = 0;

	template <class T>
	T									_addEntry(std::string& strEntryFilePathOrData, bool bParam1IsFilePath = true, std::string strEntryName = "");
	virtual void*						addEntryViaFile(std::string& strEntryFilePath, std::string strEntryName = "");
	virtual void*						addEntryViaData(std::string strEntryName, std::string& strEntryData);
	virtual void						addEntryAfter(bxcf::FormatEntry *pFormatEntry) {}

	virtual void						updateEntryCountText(void) {}

	virtual void						render(void) {}

	void								unload(void) {}

	void								processThread(void);
	void								processThreadOnce(void);

	virtual void						setFileInfoText(void) {}
	virtual void						updateTabText(void);

	virtual void								onEntryChange(bxcf::FormatEntry *pEntry) {}

	virtual uint32								getTotalEntryCount(void) { return 0; }
	virtual uint32								getSelectedEntryCount(void) { return 0; }
	virtual std::vector<bxcf::FormatEntry*>		getSelectedEntries(void) { return std::vector<bxcf::FormatEntry*>(); }
	bxcf::FormatEntry*							getSelectedEntry(void) { return getSelectedEntries()[0]; }
	virtual void								recreateEntryList(void) {}
	virtual void								removeAllEntries(void) {}
	virtual void								removeEntries(std::vector<bxcf::FormatEntry*>& vecEntries) {}
	void										removeSelectedEntries(void) { removeEntries(getSelectedEntries()); }
	virtual void								removeSelectedText(void) {}
	virtual void								removeAllText(void) {}
	void										setSelectedEntriesNameCase(uint32 uiNameCaseType);
	virtual void								copySelectedEntryData(uint32 uiColumnType);
	virtual void								shiftSelectedEntries(int32 uiRowCountOffset); // todo - rename parameter to i not ui
	std::vector<bxcf::FormatEntry*>				getEntriesByNumericMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, uint32 uiValue1, uint32 uiValue2);
	std::vector<bxcf::FormatEntry*>				getEntriesByStringMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, std::string& strValue1, std::string& strValue2, bool bMatchWildcard);
	virtual void								setEntriesSelected(std::vector<bxcf::FormatEntry*>& vecEntries, bool bIsSelected) {}
	virtual void								setEntrySelected(bxcf::FormatEntry* pEntry, bool bIsSelected) {}
	virtual bool								isEntrySelected(bxcf::FormatEntry* pEntry) { return false; }
	virtual void								onSortEntries(std::vector<bxcf::FormatEntry*>& vecEntries) {}
	virtual void								merge(std::string& strFilePath) {}
	std::vector<bxcf::FormatEntry*>				getAllEntries(void) { return getContainerFile()->getAllEntries(); }
	std::vector<bxcf::FormatEntry*>&			getEntriesRef(void) { return getContainerFile()->getEntriesRef(); }
	virtual void								setAllLinesSelected(bool bIsSelected) {}
	virtual std::vector<std::string>			getSelectedTextLines(void) { std::vector<std::string> vecTextLines; return vecTextLines; }
	virtual std::vector<std::string>			getTextLines(void) { std::vector<std::string> vecTextLines; return vecTextLines; }
	virtual void								split(std::vector<std::string>& vecTextLines, std::string& strFilePathOut, uint32 uiFileVersionOut) {}

	void								startDragDrop(imgf::EditorTab *pEditorTab, std::string strFileExtension = "");
	void								startDragDrop2(imgf::EditorTab *pEditorTab, std::vector<std::string>& vecFileNames, std::vector<std::string>& vecFileDatas);

	void								setEditor(Editor* pEditor) { m_pEditor = pEditor; }
	Editor*								getEditor(void) { return m_pEditor; }

	void								setTab(bxgx::Tab *pTab) { m_pTab = pTab; }
	bxgx::Tab*							getTab(void) { return m_pTab; }

	void								clearLogs(void);

	uint32								getTabIndex(void);

	void								setFile(bxcf::Format *pFile) { m_pFile = pFile; }
	bxcf::Format*						getFile(void) { return m_pFile; }
	bxcf::ContainerFormat*				getContainerFile(void) { return (bxcf::ContainerFormat*)m_pFile; }

	void								setMarkedToClose(bool bMarkedToClose) { m_bMarkedToClose = bMarkedToClose; }
	bool								isMarkedToClose(void) { return m_bMarkedToClose; }

	void								setThreadHasTerminated(bool bThreadHasTerminated) { m_bThreadHasTerminated = bThreadHasTerminated; }
	bool								hasThreadTerminated(void) { return m_bThreadHasTerminated; }

	std::thread&						getThread(void) { return m_thread; }

	void								onTaskProgress(void);
	void								onUnserializeFileProgress(bxcf::DataReader *pDataReader);

	void								log(std::string strText);
	void								logf(std::string strFormatText, ...);

	bxcf::VectorPool<bxgx::RenderItem*>	getRenderItems(void) { return m_vecRenderItems; }
	bxcf::VectorPool<std::string>		getLogLines(void) { return m_vecLogLines; }

	bxgx::ProgressBar*					getProgressBar(void) { return m_pProgressBar; }
	bxgx::TextBox*						getSearchBox(void) { return m_pSearchBox; }
	bxgx::TextBox*						getLog(void) { return m_pLog; }

	std::vector<bxgx::Button*>&			getButtonsPressedPending(void) { return m_vecButtonsPressedPending; }
	std::vector<bxgx::MenuItem*>&		getMenuItemsPressed(void) { return m_vecMenuItemsPressed; }

	void								setFileUnsaved(bool bFileUnsaved) { m_bFileUnsaved = bFileUnsaved; }
	bool								isFileUnsaved(void) { return m_bFileUnsaved; }

	void								setLayer(bxgx::Layer *pLayer) { m_pLayer = pLayer; }
	bxgx::Layer*						getLayer(void) { return m_pLayer; }

	void								setBaseLayer(bxgx::Layer *pBaseLayer) { m_pBaseLayer = pBaseLayer; }
	bxgx::Layer*						getBaseLayer(void) { return m_pBaseLayer; }

	void								onChangeTextBox(bxgx::TextBox *pTextBox);

protected:
	virtual void						storeControls(void);

public:
	bxgx::Text*							m_pText_FilePath;
	bxgx::Text*							m_pText_FileVersion;
	bxgx::Text*							m_pText_FileGame;
	bxgx::Text*							m_pText_FileEntryCount;

protected:
	bxcf::Format*						m_pFile;
	Editor*								m_pEditor;

	bxgx::TextBox*						m_pSearchBox;
	bxgx::Tab*							m_pTab;
	bxgx::TextBox*						m_pLog;

private:
	std::thread							m_thread;
	bool								m_bMarkedToClose;
	bool								m_bThreadHasTerminated;
	bool								m_bFileUnsaved;

	bxgx::Layer*						m_pLayer;
	bxgx::Layer*						m_pBaseLayer;

	bxgx::ProgressBar*					m_pProgressBar;
	bxcf::VectorPool<bxgx::RenderItem*>	m_vecRenderItems;
	bxcf::VectorPool<std::string>		m_vecLogLines;
	std::vector<bxgx::Button*>			m_vecButtonsPressed;
	std::vector<bxgx::Button*>			m_vecButtonsPressedPending;
	std::vector<bxgx::MenuItem*>		m_vecMenuItemsPressed;
};

// add entry
template <class T>
T										imgf::EditorTab::_addEntry(std::string& strEntryFilePathOrData, bool bParam1IsFilePath, std::string strEntryName)
{
	T pResult;
	if (bParam1IsFilePath)
	{
		if (strEntryName == "")
		{
			strEntryName = bxcf::Path::getFileName(strEntryFilePathOrData);
		}
		pResult = (T) getContainerFile()->addEntryViaFile(strEntryFilePathOrData, strEntryName);
	}
	else
	{
		pResult = (T) getContainerFile()->addEntryViaData(strEntryName, strEntryFilePathOrData);
	}
	addEntryAfter(pResult);
	updateEntryCountText();
	getLayer()->getWindow()->render();

	return pResult;
}