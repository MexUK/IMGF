#ifndef CRWSectionDepthData_H
#define CRWSectionDepthData_H

#include "bxgi.h"
#include "Type/Types.h"

class bxgi::CRWSectionDepthData
{
public:
	CRWSectionDepthData(void) :
		m_uiSectionId(0),
		m_uiSectionSize(0),
		m_uiSectionByteCountRead(0)
	{};

	void					setSectionId(uint32 uiSectionId) { m_uiSectionId = uiSectionId; }
	uint32					getSectionId(void) { return m_uiSectionId; }

	void					setSectionSize(uint32 uiSectionSize) { m_uiSectionSize = uiSectionSize; }
	uint32					getSectionSize(void) { return m_uiSectionSize; }

	void					increaseSectionByteCountRead(uint32 uiSectionByteCountReadIncrease) { m_uiSectionByteCountRead += uiSectionByteCountReadIncrease; }
	void					setSectionByteCountRead(uint32 uiSectionByteCountRead) { m_uiSectionByteCountRead = uiSectionByteCountRead; }
	uint32					getSectionByteCountRead(void) { return m_uiSectionByteCountRead; }

private:
	uint32					m_uiSectionId;
	uint32					m_uiSectionSize;
	uint32					m_uiSectionByteCountRead;
};

#endif