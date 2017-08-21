#include "CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "Task/CTaskDurationManager.h"
#include "Static/CString2.h"
#include "Static/CPath.h"
#include "Static/CFile.h"
#include "Static/CStdVector.h"
#include "Settings/CSettingsManager.h"
#include "GUI/Window/CWindowManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Layers/CMainLayer.h"
#include "Controls/CProgressControl.h"
#include "CIMGF.h"

using namespace std;
using namespace bxcf;

// constructor/destructor
CTaskManager::CTaskManager(void) :
	m_uiTaskProgressTickCount(0),
	m_uiTaskMaxProgressTickCount(0)
{
	m_pTaskDispatchManager = new CTaskDispatchManager;
	m_pTaskDurationManager = new CTaskDurationManager;
}

CTaskManager::~CTaskManager(void)
{
	delete m_pTaskDispatchManager;
}

// initialization
void							CTaskManager::init(void)
{
	m_pTaskDispatchManager->init();
}

void							CTaskManager::uninit(void)
{
	m_pTaskDispatchManager->uninit();
}

// task start/stop
void							CTaskManager::onStartTask(string strTaskName)
{
	m_vecActiveTaskNames.push_back(strTaskName);
	m_pTaskDurationManager->onStartTask(strTaskName);
}

void							CTaskManager::onCompleteTask(void)
{
	string& strTaskName = m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];

	// task duration
	m_pTaskDurationManager->onCompleteTask(strTaskName);

	// auto save
	if (getIMGF()->getSettingsManager()->getSettingBool("AutoSave"))
	{
		if (strTaskName != "onRequestOpen" &&
			strTaskName != "onRequestOpen2" &&
			strTaskName != "onRequestOpenLast" &&
			strTaskName != "onRequestClose" &&
			strTaskName != "onRequestClose2" &&
			strTaskName != "onRequestRebuild" &&
			strTaskName != "onRequestRebuildAs" &&
			strTaskName != "onRequestRebuildAll" &&
			strTaskName != "onRequestEntryViewer" &&
			strTaskName != "onRequestSearchText" &&
			strTaskName != "onRequestFind" &&
			strTaskName != "onRequestSettings" &&
			strTaskName != "onRequestFilter" &&
			strTaskName != "onRequestSearchSelection")
		{
			getIMGF()->getTaskManager()->getDispatch()->onRequestRebuild();
		}
	}

	// clean up
	m_vecActiveTaskNames.pop_back();
}

void							CTaskManager::onAbortTask(void)
{
	string& strTaskName = m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];

	// task duration
	m_pTaskDurationManager->onAbortTask(strTaskName);

	// clean up
	m_vecActiveTaskNames.pop_back();
}

// task pause/resume
void							CTaskManager::onPauseTask(void)
{
	m_pTaskDurationManager->onPauseTask();
}

void							CTaskManager::onResumeTask(void)
{
	m_pTaskDurationManager->onResumeTask();
}

// active tasks
string g_strBlankString2 = ""; // todo
string&					CTaskManager::getPreviousTaskName(void)
{
	if (m_vecActiveTaskNames.size() == 0)
	{
		return g_strBlankString2;
	}
	else
	{
		return m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];
	}
}

// task progress
void							CTaskManager::onTaskProgressTick(void)
{
	//setTaskProgressTickCount(getTaskProgressTickCount() + 1);

	static CProgressControl *pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getMainLayer()->m_pProgressBar;
	pProgressBar->increaseCurrent();
}

void							CTaskManager::onTaskProgressComplete(void)
{
	setTaskProgressTickCount(getTaskProgressTickCount() + 1);

	/*
	todo
	CProgressCtrl *pProgressCtrl = (CProgressCtrl*)getDialog()->GetDlgItem(60);
	pProgressCtrl->SetPos(getProgressTicks());
	*/
}

void							CTaskManager::setTaskMaxProgressTickCount(uint32 uiProgressMaxTicks, bool bReset)
{
	if (bReset)
	{
		setTaskProgressTickCount(0);
	}
	m_uiTaskMaxProgressTickCount = uiProgressMaxTicks;

	/*
	todo
	CProgressCtrl *pProgressCtrl = (CProgressCtrl*)getDialog()->GetDlgItem(60);
	pProgressCtrl->SetRange(0, (short)m_uiProgressMaxTicks);
	if (bReset)
	{
	pProgressCtrl->SetPos(0);
	}
	*/
}