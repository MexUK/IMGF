#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include <string>
#include <vector>

class imgf::TaskDispatchManager;
class imgf::TaskDurationManager;

class imgf::TaskManager : public bxcf::CManager
{
public:
	TaskManager(void);
	~TaskManager(void);
	
	void										init(void);
	void										uninit(void);

	TaskDispatchManager*						getDispatch(void) { return m_pTaskDispatchManager; }
	TaskDurationManager*						getDurationManager(void) { return m_pTaskDurationManager; }

	void										onStartTask(std::string strTaskName);
	void										onCompleteTask(void);
	void										onAbortTask(void);
	void										onTaskEnd(std::string strTaskName, bool bFeatureAborted = false) {} // temp

	void										onPauseTask(void);
	void										onResumeTask(void);

	void										onTaskProgressTick(void);
	void										onTaskProgressComplete(void);

	inline void									setTaskProgressTickCount(uint32 uiTaskProgressTickCount) { m_uiTaskProgressTickCount = uiTaskProgressTickCount; }
	inline uint32								getTaskProgressTickCount(void) { return m_uiTaskProgressTickCount; }

	void										setTaskMaxProgressTickCount(uint32 uiTaskMaxProgressTickCount, bool bReset = true);
	inline uint32								getTaskMaxProgressTickCount(void) { return m_uiTaskMaxProgressTickCount; }

	std::string&								getTaskName(void);

private:
	TaskDispatchManager*						m_pTaskDispatchManager;
	TaskDurationManager*						m_pTaskDurationManager;

	uint32										m_uiTaskProgressTickCount;
	uint32										m_uiTaskMaxProgressTickCount;

	std::vector<std::string>					m_vecActiveTaskNames;
};