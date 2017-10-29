#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"

class imgf::ItemPlacementEditorTab : public imgf::EditorTab
{
public:
	ItemPlacementEditorTab(void);

	void						addControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);

	void						setIPLFile(bxgi::IPLFormat *pIPLFile) { m_pIPLFile = pIPLFile; }
	bxgi::IPLFormat*			getIPLFile(void) { return m_pIPLFile; }

private:
	bxgi::IPLFormat*			m_pIPLFile;

	bxgx::TextBox*				m_pTextBox;
};