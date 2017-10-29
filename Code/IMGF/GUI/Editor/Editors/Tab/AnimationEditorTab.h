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
	void						updateEntryCountText(void);

	//void						setIFPFile(bxgi::IFPFormat *pIFPFile) { m_pIFPFile = pIFPFile; }
	//bxgi::IFPFormat*			getIFPFile(void) { return m_pIFPFile; }

private:
	//bxgi::IFPFormat*			m_pIFPFile;
};