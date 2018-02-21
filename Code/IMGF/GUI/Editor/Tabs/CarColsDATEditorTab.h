#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "nsbxgx.h"
#include "GUI/Editor/Base/EditorTab.h"
#include "GUI/Editor/Components/LeftEntryList.h"
#include "GUI/Editor/Entries/TextureEditorTabEntry.h"
#include "Pool/VectorPool.h"

class imgf::CarColsDATEditorTab //: public imgf::EditorTab, public bxcf::VectorPool<uint32>
{
public:
	CarColsDATEditorTab(void);
	~CarColsDATEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						render(void);

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
	void								merge(std::string& strFilePath);

	void						renderDisplayType_Single(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						onUnserializeRWSection(bxgi::RWSection *pRWSection);

	void						addEntryAfter(bxcf::FormatEntry *pEntry);

protected:
	void						storeControls(void);

	void						initLayer(void);

	void						onSelectDropDownItem(bxgx::DropDownItem *pItem);
	bool						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	void						onLeftMouseUp(bxcf::Vec2i vecCursorPosition);
	void						onMouseMove(bxcf::Vec2i vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

	bool						doesTabEntryMatchFilter(TextureEditorTabEntry *pTabEntry);

private:
	bool						prepareRenderData(void);

	void						prepareTexture(bxgi::RWSection_TextureNative *pRWSection_TextureNative);

	void						calculateDisplayedEntryCount(void);

private:
	//bxgi::DATCarColsFormat*		m_pDATCarColsFile;
};