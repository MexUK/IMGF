#pragma once

#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/EditorTab.h"

class imgf::AnimationEditorTab : public imgf::EditorTab
{
public:
	AnimationEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						render_Type1(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	//void						setIFPFile(bxgi::IFPFormat *pIFPFile) { m_pIFPFile = pIFPFile; } // todo
	//bxgi::IFPFormat*			getIFPFile(void) { return m_pIFPFile; }

protected:
	void						storeControls(void);

private:
	//bxgi::IFPFormat*			m_pIFPFile;
};