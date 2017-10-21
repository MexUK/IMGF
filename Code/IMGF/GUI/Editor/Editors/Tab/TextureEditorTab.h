#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Pool/VectorPool.h"

class imgf::TextureEditorTab : public imgf::EditorTab, public bxcf::VectorPool<imgf::TextureEditorTabEntry*>
{
public:
	TextureEditorTab(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						updateTabText(void);

	void						setTXDFile(bxgi::TXDFormat *pTXDFile) { m_pTXDFile = pTXDFile; }
	bxgi::TXDFormat*			getTXDFile(void) { return m_pTXDFile; }

	void						renderDisplayType_Single(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

protected:
	void						addControls(void);
	void						initControls(void);

private:
	bool						prepareRenderData_TXD(void);
	bool						prepareRenderData_WTD(void); // todo - merge with prepareRenderData_TXD?

	void						setActiveEntry(TextureEditorTabEntry *pTabEntry) { m_pActiveTabEntry = pTabEntry; }
	TextureEditorTabEntry*		getActiveEntry(void) { return m_pActiveTabEntry; }

	float32						getZoomLevel(void) { return 1.0f; }

private:
	bxgi::TXDFormat*			m_pTXDFile;
	TextureEditorTabEntry*		m_pActiveTabEntry;
};