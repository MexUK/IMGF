#include "CTaskDurationManager.h"
#include "Format/Text/INI/CINIManager.h"
#include "Static/CString2.h"
#include "Static/CTokens.h"
#include "Static/CAppDataPath.h"
#include "IMGF.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

CTaskDurationManager::CTaskDurationManager(void) :
	m_uiTaskPauseStartTime(0)
{
}

// task start/stop
void				CTaskDurationManager::onStartTask(string& strTaskName)
{
	uint32 uiTaskBeginTime = GetTickCount();
	m_vecTaskBeginTimes.push_back(uiTaskBeginTime);
	m_vecTaskPauseDurations.push_back(0);
}

void				CTaskDurationManager::onCompleteTask(string& strTaskName)
{
	uint32
		uiTimeNow = GetTickCount(),
		uiTaskIndex = m_vecTaskBeginTimes.size() - 1,
		uiTaskProcessingTime = (uiTimeNow - m_vecTaskBeginTimes[uiTaskIndex]) - m_vecTaskPauseDurations[uiTaskIndex];

	m_vecTaskBeginTimes.pop_back();
	m_vecTaskPauseDurations.pop_back();
	m_uiTaskPauseStartTime = 0;

	addTaskDuration(strTaskName, uiTaskProcessingTime);
}

void				CTaskDurationManager::onAbortTask(string& strTaskName)
{
	m_vecTaskBeginTimes.pop_back();
	m_vecTaskPauseDurations.pop_back();
	m_uiTaskPauseStartTime = 0;
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
	for (uint32 uiTaskIndex2 : m_vecTaskPauseDurations)
	{
		m_vecTaskPauseDurations[uiTaskIndex2] += uiTaskPausedDuration;
	}
}

// task durations
void				CTaskDurationManager::addTaskDuration(string& strTaskName, uint32 uiTaskDuration)
{
	CINIManager::setItem(
		CAppDataPath::getTaskDurationsPath(),
		STORAGE_SECTION,
		strTaskName,
		CTokens::addTokenRightShiftMax(getTaskDurationsString(strTaskName), CString2::toString(uiTaskDuration), VALUE_TOKEN_DELIMITER, MAX_DURATIONS_PER_TASK)
	);
}

string				CTaskDurationManager::getTaskDurationsString(string& strTaskName)
{
	return CINIManager::getItem(CAppDataPath::getTaskDurationsPath(), STORAGE_SECTION, strTaskName);
}