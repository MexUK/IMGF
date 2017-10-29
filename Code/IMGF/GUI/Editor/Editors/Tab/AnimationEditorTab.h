#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"

class imgf::AnimationEditorTab : public imgf::EditorTab
{
public:
	AnimationEditorTab(void);

	void						addControls(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						render_Type1(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);

	//void						setPLGFile(bxgi::PLGFormat *pPLGFile) { m_pPLGFile = pPLGFile; }
	//bxgi::PLGFormat*			getPLGFile(void) { return m_pPLGFile; }

private:
	//bxgi::PLGFormat*			m_pPLGFile;
};