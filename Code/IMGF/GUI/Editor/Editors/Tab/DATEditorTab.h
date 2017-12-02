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

	void						merge(std::string& strFilePath);
	void						mergeViaData(std::string& strFileData);

	void						split(std::vector<std::string>& vecTextLines, std::string& strFilePathOut, uint32 uiFileVersionOut);

	void						setAllLinesSelected(bool bIsSelected);
	std::vector<std::string>	getSelectedTextLines(void);
	uint32						getSelectedEntryCount(void);
	uint32						getTotalEntryCount(void);
	std::vector<std::string>	getTextLines(void);

	void*						addEntryViaFile(std::string& strEntryFilePath, std::string strEntryName = "");
	void*						addEntryViaData(std::string strEntryName, std::string& strEntryData);

	void						removeSelectedText(void);
	void						removeAllText(void);

	void						shiftSelectedEntries(int32 iRowCountOffset);

	void						copySelectedEntryData(uint32 uiFieldId);

private:
	bxgi::DATLoaderFormat*		m_pDATFile;

	bxgx::TextBox*				m_pTextBox;
};