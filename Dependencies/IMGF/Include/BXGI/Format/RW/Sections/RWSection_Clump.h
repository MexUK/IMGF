#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"

class bxgi::RWSection_Clump : public bxgi::RWSection
{
public:
	RWSection_Clump(void);

	void							unserialize(void);
	void							serialize(void);

	void							setAtomicallyLinkedObjectCount(uint32 uiAtomicallyLinkedObjectCount) { m_uiAtomicallyLinkedObjectCount = uiAtomicallyLinkedObjectCount; }
	uint32							getAtomicallyLinkedObjectCount(void) { return m_uiAtomicallyLinkedObjectCount; }

	void							setLightCount(uint32 uiLightCount) { m_uiLightCount = uiLightCount; }
	uint32							getLightCount(void) { return m_uiLightCount; }

	void							setCameraCount(uint32 uiCameraCount) { m_uiCameraCount = uiCameraCount; }
	uint32							getCameraCount(void) { return m_uiCameraCount; }

	bool							doesHaveLightAndCameraCounts(void); // todo

private:
	uint32							m_uiAtomicallyLinkedObjectCount;
	uint32							m_uiLightCount;
	uint32							m_uiCameraCount;
};