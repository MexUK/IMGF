#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "nsbxgx.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "GUI/Editor/Components/LeftEntryList.h"
#include "Pool/VectorPool.h"

class imgf::TextureEditorTab : public imgf::EditorTab, public imgf::LeftEntryList, public bxcf::VectorPool<imgf::TextureEditorTabEntry*>
{
public:
	TextureEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

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

protected:
	void						addControls(void);
	void						initControls(void);

	void						onSelectDropDownItem(bxgx::DropDownItem *pItem);
	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

private:
	bool						prepareRenderData_TXD(void);
	bool						prepareRenderData_WTD(void); // todo - merge with prepareRenderData_TXD?

	void						setActiveEntry(TextureEditorTabEntry *pTabEntry) { m_pActiveTabEntry = pTabEntry; }
	TextureEditorTabEntry*		getActiveEntry(void) { return m_pActiveTabEntry; }

	void						setZoomLevel(float32 fZoomLevel) { m_fZoomLevel = fZoomLevel; }
	float32						getZoomLevel(void) { return m_fZoomLevel; }

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
};