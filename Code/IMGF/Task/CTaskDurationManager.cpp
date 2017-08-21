#include "CTaskDurationManager.h"
#include "Format/Text/INI/CINIManager.h"
#include "Static/CString2.h"
#include "Static/CTokens.h"
#include "CIMGF.h"

using namespace std;
using namespace bxcf;

CTaskDurationManager::CTaskDurationManager(void) :
	m_uiTaskPauseStartTime(0),
	m_uiTasksPauseDuration(0)
{
}

// task start/stop
void				CTaskDurationManager::onStartTask(string& strTaskName)
{
	uint32 uiTaskBeginTime = GetTickCount();
	m_vecTaskBeginTimes.push_back(uiTaskBeginTime);
}

void				CTaskDurationManager::onCompleteTask(string& strTaskName)
{
	uint32
		uiTimeNow = GetTickCount(),
		uiFeatureProcessingTime = (uiTimeNow - m_vecTaskBeginTimes[m_vecTaskBeginTimes.size() - 1]) - m_uiTasksPauseDuration;

	m_vecTaskBeginTimes.pop_back();
	m_uiTaskPauseStartTime = 0;
	m_uiTasksPauseDuration = 0;

	addTaskDuration(strTaskName, uiFeatureProcessingTime);
}

void				CTaskDurationManager::onAbortTask(string& strTaskName)
{
	m_vecTaskBeginTimes.pop_back();
	m_uiTaskPauseStartTime = 0;
	m_uiTasksPauseDuration = 0;
}

// task pause/resume
void				CTaskDurationManager::onPauseTask(void)
{
	m_uiTaskPauseStartTime = GetTickCount();
}

void				CTaskDurationManager::onResumeTask(void)
{
	uint32
		uiResumeTaskTime = GetTickCount(),
		uiTaskPausedDuration = uiResumeTaskTime - m_uiTaskPauseStartTime;

	m_uiTaskPauseStartTime = 0;
	m_uiTasksPauseDuration += uiTaskPausedDuration;
}

// task durations
void				CTaskDurationManager::addTaskDuration(string& strTaskName, uint32 uiTaskDuration)
{
	CINIManager::setItem(
		getStorageFilePath(),
		STORAGE_SECTION,
		strTaskName,
		CTokens::addTokenRightShiftMax(getTaskDurationsString(strTaskName), CString2::toString(uiTaskDuration), VALUE_TOKEN_DELIMITER, MAX_DURATIONS_PER_TASK)
	);
}

string				CTaskDurationManager::getTaskDurationsString(string& strTaskName)
{
	return CINIManager::getItem(getStorageFilePath(), STORAGE_SECTION, strTaskName);
}

// task duration settings
uint32				CTaskDurationManager::getMaxDurationsPerTask(void)
{
	return MAX_DURATIONS_PER_TASK;
}

string			CTaskDurationManager::getStorageFilePath(void)
{
	return getIMGF()->getInstallationMeta().getLocalAppPath() + RELATIVE_STORAGE_FILE_PATH;
}