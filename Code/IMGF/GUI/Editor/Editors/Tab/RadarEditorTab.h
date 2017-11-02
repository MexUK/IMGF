#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Pool/VectorPool.h"

class imgf::RadarEditorTab : public imgf::EditorTab, public bxcf::VectorPool<imgf::RadarEditorTabEntry*>
{
public:
	RadarEditorTab(void);

	void						addControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						onUnserializeEntry(bxgi::IMGFormat *img);

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

	void						setActiveEntry(RadarEditorTabEntry *pTabEntry) { m_pActiveTabEntry = pTabEntry; }
	RadarEditorTabEntry*		getActiveEntry(void) { return m_pActiveTabEntry; }

protected:
	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

private:
	bxgi::IMGFormat*			m_pIMGFile;
	RadarEditorTabEntry*		m_pActiveTabEntry;

	bxgx::ScrollBar*			m_pVScrollBar;
};