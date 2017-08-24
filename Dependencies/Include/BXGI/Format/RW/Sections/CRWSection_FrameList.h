#ifndef CRWSection_FrameList_H
#define CRWSection_FrameList_H

#include "bxgi.h"
#include "Format/RW/CRWSection.h"
#include <string>

class bxgi::CRWSection_FrameList : public bxgi::CRWSection
{
public:
	bxgi::CRWSection_FrameList(void);

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

#endif