#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include "Object/Singleton.h"
#include <string>
#include <map>
#include <vector>

class bxcf::Timing : public bxcf::Singleton<Timing>
{
public:
	void										start(std::string strTimingName);
	void										stop(void);

	std::map<std::string, std::vector<uint32>>&	getTimings(void) { return m_umapTimings; }

	std::string									joinTimings(std::vector<uint32>& vecTimings);

private:
	uint32										pollTime(void);

private:
	uint32										m_uiTimeStart;
	std::map<std::string, std::vector<uint32>>	m_umapTimings;
	std::string									m_strTimingName;
};