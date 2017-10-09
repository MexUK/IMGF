#pragma once

#include "nsimgf.h"
#include "GUI/Input/EInputItem.h"
#include <string>

class imgf::Task
{
public:
	imgf::mainLayer::input::EInputItem				m_uiTaskId;
	std::string										m_strTaskName;
	void											(imgf::Tasks::* m_pTaskFunction)(void);

public:
	void											setTaskName(std::string& strTaskName) { m_strTaskName = strTaskName; }
	std::string&									getTaskName(void) { return m_strTaskName; }
};