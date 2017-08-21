#pragma once

#include "Type/Types.h"
#include <string>
#include <vector>

class CTaskDurationManager
{
private:
	const uint32			MAX_DURATIONS_PER_TASK = 100;
	const std::string		RELATIVE_STORAGE_FILE_PATH = "Data\\TaskDurations.ini";
	const std::string		STORAGE_SECTION = "TaskDurations";
	const std::string		VALUE_TOKEN_DELIMITER = " ";

public:
	CTaskDurationManager(void);

	void					onStartTask(std::string& strTaskName);
	void					onCompleteTask(std::string& strTaskName);
	void					onAbortTask(std::string& strTaskName);

	void					onPauseTask(void);
	void					onResumeTask(void);

	void					addTaskDuration(std::string& strTaskName, uint32 uiTaskDuration); // uiTaskDuration: in milliseconds
	std::string				getTaskDurationsString(std::string& strTaskName); // return: a string of space-delimited tokens in milliseconds

	std::vector<uint32>&	getTaskBeginTimes(void) { return m_vecTaskBeginTimes; } // in milliseconds, indexes are sync'd with CTaskManager::m_vecActiveTaskNames

	void					setTaskPauseStartTime(uint32 uiTaskPauseStartTime) { m_uiTaskPauseStartTime = uiTaskPauseStartTime; } // in milliseconds
	uint32					getTaskPauseStartTime(void) { return m_uiTaskPauseStartTime; } // in milliseconds

	void					setTasksPauseDuration(uint32 uiTasksPauseDuration) { m_uiTasksPauseDuration = uiTasksPauseDuration; } // in milliseconds
	uint32					getTasksPauseDuration(void) { return m_uiTasksPauseDuration; } // in milliseconds

private:
	uint32					getMaxDurationsPerTask(void);
	std::string				getStorageFilePath(void);

private:
	std::vector<uint32>		m_vecTaskBeginTimes; // in milliseconds, indexes are sync'd with CTaskManager::m_vecActiveTaskNames
	uint32					m_uiTaskPauseStartTime; // in milliseconds
	uint32					m_uiTasksPauseDuration; // in milliseconds
};