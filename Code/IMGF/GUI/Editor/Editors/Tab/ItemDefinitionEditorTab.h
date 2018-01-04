#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include <string>
#include <vector>

class imgf::ItemDefinitionEditorTab : public imgf::EditorTab
{
public:
	ItemDefinitionEditorTab(void);

	void						addControls(void);

	void						initLayer(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						setIDEFile(bxgi::IDEFormat *pIDEFile) { m_pIDEFile = pIDEFile; }
	bxgi::IDEFormat*			getIDEFile(void) { return m_pIDEFile; }








	// todo
	//std::vector<bxcf::FormatEntry*>				getAllEntries(void) { return (std::vector<bxcf::FormatEntry*>)(std::vector<bxcf::FormatEntry*>&)m_pTextBox->getTextLines(); }
	//std::vector<bxcf::FormatEntry*>&			getEntriesRef(void) { return (std::vector<bxcf::FormatEntry*>&)m_pTextBox->getTextLines(); }

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	void						setAllLinesSelected(bool bIsSelected);
	std::vector<std::string>	getSelectedTextLines(void);
	uint32						getSelectedEntryCount(void);
	uint32						getTotalEntryCount(void);
	std::vector<std::string>	getTextLines(void);

	void						merge(std::string& strFilePath);
	void						mergeViaData(std::string& strFileData);

	void						split(std::vector<std::string>& vecTextLines, std::string& strFilePathOut, uint32 uiFileVersionOut);

	void*						addEntryViaFile(std::string& strEntryFilePath, std::string strEntryName = "");
	void*						addEntryViaData(std::string strEntryName, std::string& strEntryData);

	void						removeSelectedText(void);
	void						removeAllText(void);

	void						shiftSelectedEntries(int32 iRowCountOffset);

	void						copySelectedEntryData(uint32 uiFieldId);

private:
	bxgi::IDEFormat*			m_pIDEFile;

	bxgx::TextBox*				m_pTextBox;
};