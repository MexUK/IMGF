#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Pool/VectorPool.h"
#include "Format/FormatEntry.h"
#include "GUI/Editor/Editors/Entry/RadarEditorTabEntry.h"
#include <vector>

class imgf::RadarEditorTab : public imgf::EditorTab, public bxcf::VectorPool<imgf::RadarEditorTabEntry*>
{
public:
	RadarEditorTab(void);

	void						addControls(void);
	void						initControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						onUnserializeEntry(bxgi::IMGFormat *img);

	uint32								getTotalEntryCount(void);
	std::vector<bxcf::FormatEntry*>		getSelectedEntries(void);
	uint32								getSelectedEntryCount(void);
	void								onEntryChange(bxcf::FormatEntry *pEntry);
	void								recreateEntryList(void);
	void								removeAllEntries(void);
	void								removeEntries(std::vector<bxcf::FormatEntry*>& vecEntries);
	void								setEntriesSelected(std::vector<bxcf::FormatEntry*>& vecEntries, bool bIsSelected);

	void						renderEntryList(void);
	void						render_Type1(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						prepareRenderData_TXD(void);
	void						prepareRenderData_WTD(void);

	void						setIMGFile(bxgi::IMGFormat *pIMGFile) { m_pIMGFile = pIMGFile; }
	bxgi::IMGFormat*			getIMGFile(void) { return m_pIMGFile; }

	void						setActiveEntry(RadarEditorTabEntry *pTabEntry) { m_pActiveTabEntry = pTabEntry; if (pTabEntry) pTabEntry->m_bIsActive = true; }
	RadarEditorTabEntry*		getActiveEntry(void) { return m_pActiveTabEntry; }
	void						clearActiveEntries(void);

	bool						doesTabEntryMatchFilter(RadarEditorTabEntry *pTabEntry);

protected:
	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeChange);

	uint32						getFileIndexFromEntry(bxcf::FormatEntry *pFormatEntry);

	RadarEditorTabEntry*		getEntryByIMGEntry(bxgi::IMGEntry *pIMGEntry);

	void						addEntryAfter(bxcf::FormatEntry *pEntry);

	void						calculateDisplayedEntryCount(void);

private:
	bxgi::IMGFormat*			m_pIMGFile;
	RadarEditorTabEntry*		m_pActiveTabEntry;

	bxgx::ScrollBar*			m_pVScrollBar;
	uint32						m_uiDisplayedEntryCount;

	std::vector<bxgi::TXDFormat*>		m_vecTXDFiles;
	std::vector<bxgi::WTDFormat*>		m_vecWTDFiles;
};