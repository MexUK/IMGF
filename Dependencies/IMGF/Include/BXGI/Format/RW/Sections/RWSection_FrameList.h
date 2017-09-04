#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"
#include <string>

class bxgi::RWSection_FrameList : public bxgi::RWSection
{
public:
	bxgi::RWSection_FrameList(void);

	void							unserialize(void);
	void							serialize(void);

	void							setFrameCount(uint32 uiFrameCount) { m_uiFrameCount = uiFrameCount; }
	uint32							getFrameCount(void) { return m_uiFrameCount; }

	void							setFrameData(std::string& strFrameData) { m_strFrameData = strFrameData; }
	std::string&					getFrameData(void) { return m_strFrameData; }

private:
	uint32							m_uiFrameCount;
	std::string						m_strFrameData;
};