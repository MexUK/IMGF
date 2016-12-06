#ifndef CTaskManager_H
#define CTaskManager_H

#include "Type/Types.h"
#include "Object/CManager.h"
#include <string>
#include <unordered_map>

class CTaskDispatchManager;

class CTaskManager : public mcore::CManager
{
public:
	CTaskManager(void);
	~CTaskManager(void);
	
	void										init(void);
	void										uninit(void);

	CTaskDispatchManager*						getDispatch(void) { return m_pTaskDispatchManager; }

	void										onTaskBegin(std::string strFeatureName);
	void										onTaskEnd(std::string strFeatureName, bool bFeatureAborted = false);
	void										onTaskPause(void);
	void										onTaskUnpause(void);
	void										onTaskProgressTick(void);
	void										onTaskProgressComplete(void);

	void										setTaskPauseStartTime(uint32 uiTaskPauseStartTime) { m_uiTaskPauseStartTime = uiTaskPauseStartTime; }
	uint32										getTaskPauseStartTime(void) { return m_uiTaskPauseStartTime; }

	void										setTaskPauseDuration(uint32 uiTaskPauseDuration) { m_uiTaskPauseDuration = uiTaskPauseDuration; }
	uint32										getTaskPauseDuration(void) { return m_uiTaskPauseDuration; }

	void										setTaskProgressTickCount(uint32 uiTaskProgressTickCount) { m_uiTaskProgressTickCount = uiTaskProgressTickCount; }
	uint32										getTaskProgressTickCount(void) { return m_uiTaskProgressTickCount; }

	void										setTaskMaxProgressTickCount(uint32 uiTaskMaxProgressTickCount, bool bReset = true);
	uint32										getTaskMaxProgressTickCount(void) { return m_uiTaskMaxProgressTickCount; }

	void										setPreviousTaskName(std::string& strPreviousTaskName) { m_strPreviousTaskName = strPreviousTaskName; }
	std::string&								getPreviousTaskName(void) { return m_strPreviousTaskName; }

	std::unordered_map<std::string, uint32>&	getTaskBeginTimes(void) { return m_umapTaskBeginTimes; }

private:
	CTaskDispatchManager*						m_pTaskDispatchManager;

	uint32										m_uiTaskPauseStartTime; // todo - in ms or secs?
	uint32										m_uiTaskPauseDuration; // todo - in ms or secs?

	uint32										m_uiTaskProgressTickCount;
	uint32										m_uiTaskMaxProgressTickCount;

	std::string									m_strPreviousTaskName;
	std::unordered_map<std::string, uint32>		m_umapTaskBeginTimes; // todo - in ms or secs?
};

#endif