#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "nsbxgx.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "GUI/Editor/Components/LeftEntryList.h"
#include "GUI/Editor/Editors/Entry/TextureEditorTabEntry.h"
#include "Pool/VectorPool.h"

class imgf::TextureEditorTab : public imgf::EditorTab, public imgf::LeftEntryList, public bxcf::VectorPool<imgf::TextureEditorTabEntry*>
{
public:
	TextureEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	uint32								getTotalEntryCount(void);
	std::vector<bxcf::FormatEntry*>		getSelectedEntries(void);
	uint32								getSelectedEntryCount(void);
	void								onEntryChange(bxcf::FormatEntry *pEntry);
	void								recreateEntryList(void);
	void								removeAllEntries(void);
	void								removeEntries(std::vector<bxcf::FormatEntry*>& vecEntries);
	void								setEntriesSelected(std::vector<bxcf::FormatEntry*>& vecEntries, bool bIsSelected);
	void								setEntrySelected(bxcf::FormatEntry* pEntry, bool bIsSelected);
	bool								isEntrySelected(bxcf::FormatEntry* pEntry);
	void								onSortEntries(std::vector<bxcf::FormatEntry*>& vecEntries);

	void						setIsTXDFile(bool bIsTXDFile) { m_bIsTXDFile = bIsTXDFile; }
	bool						isTXDFile(void) { return m_bIsTXDFile; }

	void						setTXDFile(bxgi::TXDFormat *pTXDFile) { m_pTXDFile = pTXDFile; }
	bxgi::TXDFormat*			getTXDFile(void) { return m_pTXDFile; }

	void						setWTDFile(bxgi::WTDFormat *pWTDFile) { m_pWTDFile = pWTDFile; }
	bxgi::WTDFormat*			getWTDFile(void) { return m_pWTDFile; }

	void						renderDisplayType_Single(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						onUnserializeRWSection(bxgi::RWSection *pRWSection);

	void						addEntryAfter(bxcf::FormatEntry *pEntry);

protected:
	void						addControls(void);
	void						initControls(void);

	void						onSelectDropDownItem(bxgx::DropDownItem *pItem);
	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeChange);

	bool						doesTabEntryMatchFilter(TextureEditorTabEntry *pTabEntry);

private:
	bool						prepareRenderData_TXD(void);
	bool						prepareRenderData_WTD(void); // todo - merge with prepareRenderData_TXD?

	void						prepareTexture_TXD(bxgi::RWSection_TextureNative *pRWSection_TextureNative);
	void						prepareTexture_WTD(bxgi::WTDEntry *pWTDEntry);

	void						setActiveEntry(TextureEditorTabEntry *pTabEntry) { m_pActiveTabEntry = pTabEntry; if(pTabEntry) pTabEntry->m_bIsActive = true; }
	TextureEditorTabEntry*		getActiveEntry(void) { return m_pActiveTabEntry; }
	void						clearActiveEntries(void);

	void						setZoomLevel(float32 fZoomLevel) { m_fZoomLevel = fZoomLevel; }
	float32						getZoomLevel(void) { return m_fZoomLevel; }

	void						calculateDisplayedEntryCount(void);

private:
	bool						m_bIsTXDFile;
	union
	{
		bxgi::TXDFormat*			m_pTXDFile;
		bxgi::WTDFormat*			m_pWTDFile;
	};
	TextureEditorTabEntry*		m_pActiveTabEntry;

	bxgx::DropDown*				m_pZoomDropDown;
	bxgx::ScrollBar*			m_pVScrollBar;

	float32						m_fZoomLevel;
	uint32						m_uiDisplayedEntryCount;
};