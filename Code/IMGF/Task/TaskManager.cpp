#include "TaskManager.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Task/Tasks/Tasks.h"
#include "Task/Duration/TaskDurationManager.h"
#include "Static/String.h"
#include "Static/Path.h"
#include "Static/File.h"
#include "Static/StdVector.h"
#include "Settings/SettingsManager.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "Control/Controls/ProgressBar.h"
#include "IMGF.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace imgf;

// constructor/destructor
TaskManager::TaskManager(void) :
	m_uiTaskProgressTickCount(0),
	m_uiTaskMaxProgressTickCount(0)
{
	m_pTasks = new Tasks;
	m_pTaskDurationManager = new TaskDurationManager;
}

TaskManager::~TaskManager(void)
{
	delete m_pTasks;
}

// initialization
void							TaskManager::init(void)
{
	m_pTasks->init();
}

void							TaskManager::uninit(void)
{
	m_pTasks->uninit();
}

// task start/stop
void							TaskManager::onStartTask(string strTaskName)
{
	m_vecActiveTaskNames.push_back(strTaskName);
	m_pTaskDurationManager->onStartTask(strTaskName);
}

void							TaskManager::onCompleteTask(void)
{
	string& strTaskName = m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];

	// task duration
	m_pTaskDurationManager->onCompleteTask(strTaskName);

	// auto save
	/*
	todo
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
	*/

	// clean up
	m_vecActiveTaskNames.pop_back();
}

void							TaskManager::onAbortTask(void)
{
	string& strTaskName = m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];

	// task duration
	m_pTaskDurationManager->onAbortTask(strTaskName);

	// clean up
	m_vecActiveTaskNames.pop_back();
}

// task pause/resume
void							TaskManager::onPauseTask(void)
{
	m_pTaskDurationManager->onPauseTask();
}

void							TaskManager::onResumeTask(void)
{
	m_pTaskDurationManager->onResumeTask();
}

// active tasks
string&					TaskManager::getTaskName(void)
{
	if (m_vecActiveTaskNames.size() == 0)
	{
		return bxcf::g_strBlankString;
	}
	else
	{
		return m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];
	}
}

// task progress
void							TaskManager::onTaskProgressTick(void)
{
	//setTaskProgressTickCount(getTaskProgressTickCount() + 1);

	ProgressBar *pProgressBar;
	if (getIMGF()->getWindowManager()->getMainWindow()->getIMGEditor()->getActiveTab())
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getIMGEditor()->getActiveTab()->getProgressBar();
	}
	else
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->getProgressBar();
	}
	pProgressBar->increaseCurrent();
}

void							TaskManager::onTaskProgressComplete(void)
{
	setTaskProgressTickCount(getTaskProgressTickCount() + 1);

	/*
	todo
	ProgressBarCtrl *pProgressCtrl = (ProgressBarCtrl*)getDialog()->GetDlgItem(60);
	pProgressCtrl->SetPos(getProgressTicks());
	*/
}

void							TaskManager::setTaskMaxProgressTickCount(uint32 uiProgressMaxTicks, bool bResetCurrent)
{
	if (bResetCurrent)
	{
		setTaskProgressTickCount(0);
	}
	m_uiTaskMaxProgressTickCount = uiProgressMaxTicks;

	ProgressBar *pProgressBar;
	if (getIMGF()->getWindowManager()->getMainWindow()->getIMGEditor()->getActiveTab())
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getIMGEditor()->getActiveTab()->getProgressBar();
	}
	else
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->getProgressBar();
	}
	pProgressBar->setMax(uiProgressMaxTicks, bResetCurrent);

	/*
	todo
	ProgressBarCtrl *pProgressCtrl = (ProgressBarCtrl*)getDialog()->GetDlgItem(60);
	pProgressCtrl->SetRange(0, (short)m_uiProgressMaxTicks);
	if (bReset)
	{
	pProgressCtrl->SetPos(0);
	}
	*/
}