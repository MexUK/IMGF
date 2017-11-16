#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"

class imgf::DATEditorTab : public imgf::EditorTab
{
public:
	DATEditorTab(void);

	void						addControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						setDATFile(bxgi::DATLoaderFormat *pDATFile) { m_pDATFile = pDATFile; }
	bxgi::DATLoaderFormat*		getDATFile(void) { return m_pDATFile; }

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

private:
	bxgi::DATLoaderFormat*		m_pDATFile;

	bxgx::TextBox*				m_pTextBox;
};