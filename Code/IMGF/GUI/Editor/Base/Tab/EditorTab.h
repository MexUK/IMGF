#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Pool/VectorPool.h"
#include "Event/EventBindable.h"
#include "Event/EInputEvent.h"
#include "../BXCF/Event/EEvent.h"
#include <string>
#include <vector>
#include <thread>

class imgf::Editor;
class bxcf::Format;
class bxgx::Tab;
class bxgx::TextBox;
class bxgx::ProgressBar;

class imgf::EditorTab : public bxgx::Layer, public bxcf::EventBindable
{
public:
	EditorTab(void);
	virtual ~EditorTab(void);

	void								init(void);

	void								unload(void) {}

	void								processThread(void);
	void								processThreadOnce(void);

	virtual void						setFileInfoText(void) {}

	void								setEditor(Editor* pEditor) { m_pEditor = pEditor; }
	Editor*								getEditor(void) { return m_pEditor; }

	void								setTab(bxgx::Tab *pTab) { m_pTab = pTab; }
	bxgx::Tab*							getTab(void) { return m_pTab; }

	uint32								getTabIndex(void);

	void								setFile(bxcf::Format *pFile) { m_pFile = pFile; }
	bxcf::Format*						getFile(void) { return m_pFile; }

	void								setMarkedToClose(bool bMarkedToClose) { m_bMarkedToClose = bMarkedToClose; }
	bool								isMarkedToClose(void) { return m_bMarkedToClose; }

	void								setThreadHasTerminated(bool bThreadHasTerminated) { m_bThreadHasTerminated = bThreadHasTerminated; }
	bool								hasThreadTerminated(void) { return m_bThreadHasTerminated; }

	std::thread&						getThread(void) { return m_thread; }

	void								addControls(void);
	void								initControls(void);
	void								repositionAndResizeControls(bxcf::Vec2i& vecSizeDifference);

	void								onTaskProgress(void);

	void								log(std::string strText);
	void								logf(std::string strFormatText, ...);

	bxcf::VectorPool<RenderItem*>		getRenderItems(void) { return m_vecRenderItems; }
	bxcf::VectorPool<std::string>		getLogLines(void) { return m_vecLogLines; }

	bxgx::ProgressBar*					getProgressBar(void) { return m_pProgressBar; }
	bxgx::TextBox*						getSearchBox(void) { return m_pSearchBox; }
	bxgx::TextBox*						getLog(void) { return m_pLog; }

	std::vector<bxgx::Button*>&			getButtonsPressedPending(void) { return m_vecButtonsPressedPending; }
	std::vector<bxgx::MenuItem*>&		getMenuItemsPressed(void) { return m_vecMenuItemsPressed; }

protected:
	bxgx::TextBox*						m_pSearchBox;
	bxgx::Tab*							m_pTab;
	bxgx::TextBox*						m_pLog;

private:
	std::thread							m_thread;
	bool								m_bMarkedToClose;
	bool								m_bThreadHasTerminated;
	Editor*								m_pEditor;
	bxcf::Format*						m_pFile;
	bxgx::ProgressBar*					m_pProgressBar;
	bxcf::VectorPool<RenderItem*>		m_vecRenderItems;
	bxcf::VectorPool<std::string>		m_vecLogLines;
	std::vector<bxgx::Button*>			m_vecButtonsPressed;
	std::vector<bxgx::Button*>			m_vecButtonsPressedPending;
	std::vector<bxgx::MenuItem*>		m_vecMenuItemsPressed;
};