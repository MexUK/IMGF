#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"

class imgf::ItemDefinitionEditorTab : public imgf::EditorTab
{
public:
	ItemDefinitionEditorTab(void);

	void						addControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						setIDEFile(bxgi::IDEFormat *pIDEFile) { m_pIDEFile = pIDEFile; }
	bxgi::IDEFormat*			getIDEFile(void) { return m_pIDEFile; }

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	void						merge(std::string& strFilePath);
	void						mergeViaData(std::string& strFileData);

private:
	bxgi::IDEFormat*			m_pIDEFile;

	bxgx::TextBox*				m_pTextBox;
};