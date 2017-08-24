#ifndef CRWSection_Atomic_H
#define CRWSection_Atomic_H

#include "bxgi.h"
#include "Format/RW/CRWSection.h"

class bxgi::CRWSection_Atomic : public bxgi::CRWSection
{
public:
	CRWSection_Atomic(void);

	void							unserialize(void);
	void							serialize(void);

	void							setFrameIndex(uint32 uiFrameIndex) { m_uiFrameIndex = uiFrameIndex; }
	uint32							getFrameIndex(void) { return m_uiFrameIndex; }

	void							setGeometryIndex(uint32 uiGeometryIndex) { m_uiGeometryIndex = uiGeometryIndex; }
	uint32							getGeometryIndex(void) { return m_uiGeometryIndex; }

	void							setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32							getUnknown1(void) { return m_uiUnknown1; }

	void							setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32							getUnknown2(void) { return m_uiUnknown2; }

private:
	uint32							m_uiFrameIndex;
	uint32							m_uiGeometryIndex;
	uint32							m_uiUnknown1;
	uint32							m_uiUnknown2;
};

#endif