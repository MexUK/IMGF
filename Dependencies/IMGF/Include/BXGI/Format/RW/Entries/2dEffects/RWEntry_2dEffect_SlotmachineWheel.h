#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/RW/Entries/_2dEffect.h"

class bxgi::RWEntry_2dEffect_SlotmachineWheel : public bxgi::_2dEffect
{
public:
	RWEntry_2dEffect_SlotmachineWheel(void);

	void							unserialize(void);
	void							serialize(void);

	void							setWheelIndex(int32 iWheelIndex) { m_iWheelIndex = iWheelIndex; }
	int32							getWheelIndex(void) { return m_iWheelIndex; }

private:
	int32							m_iWheelIndex;
};