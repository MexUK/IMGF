#include "CTaskManager.h"
#include "Globals.h"
#include "CIMGF.h"
#include "CTaskDispatchManager.h"
#include "Type/String/CString2.h"
#include "Path/CPathManager.h"
#include "File/CFileManager.h"
#include "Type/StdVector/CStdVector.h"
#include "Format/Text/INI/CINIManager.h"
#include "GUI/Editors/CIMGEditor.h"
#include "CSettingsManager.h"

using namespace std;
using namespace mcore;

// construct
CTaskManager::CTaskManager(void) :
	m_uiTaskPauseStartTime(0),
	m_uiTaskPauseDuration(0),
	m_uiTaskProgressTickCount(0),
	m_uiTaskMaxProgressTickCount(0)
{
	m_pTaskDispatchManager = new CTaskDispatchManager;
}
CTaskManager::~CTaskManager(void)
{
	delete m_pTaskDispatchManager;
}

// init
void							CTaskManager::init(void)
{
	m_pTaskDispatchManager->init();
}

void							CTaskManager::uninit(void)
{
	m_pTaskDispatchManager->uninit();
}

// task pause
void							CTaskManager::onTaskPause(void)
{
	m_uiTaskPauseStartTime = GetTickCount();
}

void							CTaskManager::onTaskUnpause(void)
{
	uint32 uiTimeNow = GetTickCount();
	m_uiTaskPauseStartTime = uiTimeNow;
	uint32 uiFeaturePauseEndTime = uiTimeNow;
	uint32 uiPauseDuration = uiFeaturePauseEndTime - m_uiTaskPauseStartTime;
	m_uiTaskPauseDuration += uiPauseDuration;
	m_uiTaskPauseStartTime = 0;
}

// progress ticks
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

void							CTaskManager::onTaskProgressTick(void)
{
	setTaskProgressTickCount(getTaskProgressTickCount() + 1);

	/*
	todo
	CProgressCtrl *pProgressCtrl = (CProgressCtrl*)getDialog()->GetDlgItem(60);
	pProgressCtrl->SetPos(getProgressTicks());
	*/
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

// task state
void							CTaskManager::onTaskBegin(string strFeatureName)
{
	setPreviousTaskName(strFeatureName);
	getTaskBeginTimes()[strFeatureName] = GetTickCount();
	m_uiTaskPauseDuration = 0;
}
void							CTaskManager::onTaskEnd(string strFeatureName, bool bFeatureAborted)
{
	uint32 uiTimeNow = GetTickCount();

	/*
	todo

	if (getIMGF()->getIMGEditor()->getEntryCount() > 0)
	{
		getIMGF()->getEntryListTab()->resetOverwriteEntryOption();
	}
	*/

	if (bFeatureAborted)
	{
		return;
	}

	uint32 uiFeatureProcessingTime = (uiTimeNow - getTaskBeginTimes()[strFeatureName]) - m_uiTaskPauseDuration;
	//m_uiFeatureBeginTime = 0;
	getTaskBeginTimes().erase(getTaskBeginTimes().find(strFeatureName));
	m_uiTaskPauseDuration = 0;
	m_uiTaskPauseStartTime = 0;

	string strINIPath = getIMGF()->getInstallationMeta().getLocalAppPath() + "Data\\FeatureProcessingTimes.txt";
	if (!CFileManager::doesFolderExist(CPathManager::getDirectory(strINIPath)))
	{
		CFileManager::createFoldersForPath(strINIPath);
	}

	string strItem = CINIManager::getItem(strINIPath, "FeatureProcessingTimes", strFeatureName);
	deque<string> deqTokens;
	if (strItem != "")
	{
		deqTokens = CStdVector::convertVectorToDeque(CString2::split(strItem, " "));
	}

	if (deqTokens.size() == 100)
	{
		deqTokens.pop_front();
	}
	deqTokens.push_back(CString2::toString(uiFeatureProcessingTime));

	CINIManager::setItem(strINIPath, "FeatureProcessingTimes", strFeatureName, CString2::join(deqTokens, " "));

	// auto save
	if (getIMGF()->getSettingsManager()->getSettingBool("AutoSave"))
	{
		if (strFeatureName != "onRequestOpen" &&
			strFeatureName != "onRequestOpen2" &&
			strFeatureName != "onRequestOpenLast" &&
			strFeatureName != "onRequestClose" &&
			strFeatureName != "onRequestClose2" &&
			strFeatureName != "onRequestRebuild" &&
			strFeatureName != "onRequestRebuildAs" &&
			strFeatureName != "onRequestRebuildAll" &&
			strFeatureName != "onRequestEntryViewer" &&
			strFeatureName != "onRequestSearchText" &&
			strFeatureName != "onRequestFind" &&
			strFeatureName != "onRequestSettings" &&
			strFeatureName != "onRequestFilter" &&
			strFeatureName != "onRequestSearchSelection")
		{
			//mcore::CGUIManager::showMessage("Feature: " + strFeatureName, "Feature Causing Rebuild Bug", MB_OK);
			getIMGF()->getTaskManager()->getDispatch()->onRequestRebuild();
		}
	}
}