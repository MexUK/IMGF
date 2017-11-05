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

class imgf::EditorTab : public bxgx::Layer, public bxcf::EventBindable
{
public:
	EditorTab(void);
	virtual ~EditorTab(void);

	bool								init(bool bIsNewFile);

	virtual void						bindEvents(void);
	virtual void						unbindEvents(void);

	virtual void						addControls(void);
	virtual void						initControls(void);

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

	void								repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	void								onTaskProgress(void);
	void								onUnserializeFileProgress(bxcf::DataReader *pDataReader);

	void								log(std::string strText);
	void								logf(std::string strFormatText, ...);

	bxcf::VectorPool<RenderItem*>		getRenderItems(void) { return m_vecRenderItems; }
	bxcf::VectorPool<std::string>		getLogLines(void) { return m_vecLogLines; }

	bxgx::ProgressBar*					getProgressBar(void) { return m_pProgressBar; }
	bxgx::TextBox*						getSearchBox(void) { return m_pSearchBox; }
	bxgx::TextBox*						getLog(void) { return m_pLog; }

	std::vector<bxgx::Button*>&			getButtonsPressedPending(void) { return m_vecButtonsPressedPending; }
	std::vector<bxgx::MenuItem*>&		getMenuItemsPressed(void) { return m_vecMenuItemsPressed; }

	void								setFileUnsaved(bool bFileUnsaved) { m_bFileUnsaved = bFileUnsaved; }
	bool								isFileUnsaved(void) { return m_bFileUnsaved; }

protected:
	bxcf::Format*						m_pFile;
	Editor*								m_pEditor;

	bxgx::Text*							m_pText_FilePath;
	bxgx::Text*							m_pText_FileVersion;
	bxgx::Text*							m_pText_FileGame;
	bxgx::Text*							m_pText_FileEntryCount;

	bxgx::TextBox*						m_pSearchBox;
	bxgx::Tab*							m_pTab;
	bxgx::TextBox*						m_pLog;

private:
	std::thread							m_thread;
	bool								m_bMarkedToClose;
	bool								m_bThreadHasTerminated;
	bool								m_bFileUnsaved;

	bxgx::ProgressBar*					m_pProgressBar;
	bxcf::VectorPool<RenderItem*>		m_vecRenderItems;
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

	return pResult;
}