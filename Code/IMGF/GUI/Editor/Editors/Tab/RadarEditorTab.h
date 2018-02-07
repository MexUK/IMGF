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

	void						initLayer(void);

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
	void								merge(std::string& strFilePath);

	void						render(void);
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

	void						setMouseDownOriginEntry(RadarEditorTabEntry *pMouseDownOriginEntry) { m_pMouseDownOriginEntry = pMouseDownOriginEntry; }
	RadarEditorTabEntry*		getMouseDownOriginEntry(void) { return m_pMouseDownOriginEntry; }

	void						setActiveEntry(RadarEditorTabEntry *pTabEntry) { m_pActiveTabEntry = pTabEntry; if (pTabEntry) pTabEntry->m_bIsActive = true; }
	RadarEditorTabEntry*		getActiveEntry(void) { return m_pActiveTabEntry; }
	void						clearActiveEntries(void);

	bool						doesTabEntryMatchFilter(RadarEditorTabEntry *pTabEntry);

protected:
	void						storeControls(void);

	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);
	void						onLeftMouseUp(bxcf::Vec2i vecCursorPosition);
	void						onMouseMove(bxcf::Vec2i vecCursorPosition);

	uint32						getFileIndexFromEntry(bxcf::FormatEntry *pFormatEntry);

	RadarEditorTabEntry*		getEntryByIMGEntry(bxgi::IMGEntry *pIMGEntry);

	void						addEntryAfter(bxcf::FormatEntry *pEntry);

	void						setZoomLevel(float32 fZoomLevel) { m_fZoomLevel = fZoomLevel; }
	float32						getZoomLevel(void) { return m_fZoomLevel; }

	void						calculateDisplayedEntryCount(void);

private:
	bxgi::IMGFormat*			m_pIMGFile;
	bool						m_bInitialized;
	RadarEditorTabEntry*		m_pActiveTabEntry;

	float32						m_fZoomLevel;
	uint32						m_uiDisplayedEntryCount;
	RadarEditorTabEntry*		m_pMouseDownOriginEntry;
	bxgx::CheckBox*				m_pDiffuseCheckBox;
	bxgx::CheckBox*				m_pAlphaCheckBox;
	bxgx::DropDown*				m_pZoomDropDown;
	bxgx::ScrollBar*			m_pVScrollBar;

	std::vector<bxgi::TXDFormat*>		m_vecTXDFiles;
	std::vector<bxgi::WTDFormat*>		m_vecWTDFiles;
};