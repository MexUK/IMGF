#include "TaskDurationManager.h"
#include "Format/Text/INI/INIManager.h"
#include "Static/String2.h"
#include "Static/Tokens.h"
#include "Static/AppDataPath.h"
#include "IMGF.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

TaskDurationManager::TaskDurationManager(void) :
	m_uiTaskPauseStartTime(0)
{
}

// task start/stop
void				TaskDurationManager::onStartTask(string& strTaskName)
{
	uint32 uiTaskBeginTime = GetTickCount();
	m_vecTaskBeginTimes.push_back(uiTaskBeginTime);
	m_vecTaskPauseDurations.push_back(0);
}

void				TaskDurationManager::onCompleteTask(string& strTaskName)
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

void				TaskDurationManager::onAbortTask(string& strTaskName)
{
	m_vecTaskBeginTimes.pop_back();
	m_vecTaskPauseDurations.pop_back();
	m_uiTaskPauseStartTime = 0;
}

// task pause/resume
void				TaskDurationManager::onPauseTask(void)
{
	m_uiTaskPauseStartTime = GetTickCount();
}

void				TaskDurationManager::onResumeTask(void)
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
void				TaskDurationManager::addTaskDuration(string& strTaskName, uint32 uiTaskDuration)
{
	INIManager::setItem(
		AppDataPath::getTaskDurationsPath(),
		STORAGE_SECTION,
		strTaskName,
		Tokens::addTokenRightShiftMax(getTaskDurationsString(strTaskName), String2::toString(uiTaskDuration), VALUE_TOKEN_DELIMITER, MAX_DURATIONS_PER_TASK)
	);
}

string				TaskDurationManager::getTaskDurationsString(string& strTaskName)
{
	return INIManager::getItem(AppDataPath::getTaskDurationsPath(), STORAGE_SECTION, strTaskName);
}