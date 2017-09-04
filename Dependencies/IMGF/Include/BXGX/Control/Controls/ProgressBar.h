#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Base/Control.h"
#include "Control/Components/TextComponent.h"

class bxgx::ProgressBar : public bxgx::Control, public bxgx::TextComponent
{
public:
	ProgressBar(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onRender(void);

	bxcf::Vec2u								getSeekBarSize(void);		// in pixels
	uint32									getSeekBarSizeWidth(void);	// in pixels

	std::string								getProgressPercentText(void);

	void									setProgress(float32 fProgress) { m_fProgress = fProgress; }
	float32									getProgress(void) { return m_fProgress; }

	void									setCurrent(uint32 uiCurrent);
	uint32									getCurrent(void) { return m_uiCurrent; }
	void									increaseCurrent(void);

	void									setMax(uint32 uiMax);
	uint32									getMax(void) { return m_uiMax; }

	void									setCompletionPercentageShown(bool bCompletionPercentageShown) { m_bCompletionPercentageShown = bCompletionPercentageShown; }
	bool									isCompletionPercentageShown(void) { return m_bCompletionPercentageShown; }

	void									reset(void);

private:
	void									updateProgress(void);

private:
	float32									m_fProgress;
	uint32									m_uiCurrent;
	uint32									m_uiMax;
	uint8									m_bCompletionPercentageShown	: 1;
};