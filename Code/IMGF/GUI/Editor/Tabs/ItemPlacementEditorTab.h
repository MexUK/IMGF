#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/EditorTab.h"

class imgf::ItemPlacementEditorTab : public imgf::EditorTab
{
public:
	ItemPlacementEditorTab(void);

	void						initLayer(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						onChangeTextBox(bxgx::TextBox *pTextBox);

	void						setIPLFile(bxgi::IPLFormat *pIPLFile) { m_pIPLFile = pIPLFile; }
	bxgi::IPLFormat*			getIPLFile(void) { return m_pIPLFile; }

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

protected:
	void						storeControls(void);

private:
	bxgi::IPLFormat*			m_pIPLFile;

	bxgx::TextBox*				m_pTextBox;
};