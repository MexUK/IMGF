#ifndef CProgressControl_H
#define CProgressControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Styles/CGUIStyles.h"
#include "Controls/Components/CGUIControlComponent_Text.h"

class CProgressControl : public CGUIControl, public CGUIControlComponent_Text
{
public:
	CProgressControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onRender(void);

	bxcf::Vec2u								getSeekBarSize(void);		// in pixels
	uint32									getSeekBarSizeWidth(void);	// in pixels

	std::string								getProgressPercentText(void);

	void									setProgress(float32 fProgress) { m_fProgress = fProgress; }
	float32									getProgress(void) { return m_fProgress; }

	void									setMax(uint32 uiMax) { m_uiMax = uiMax; }
	uint32									getMax(void) { return m_uiMax; }

	void									setCompletionPercentageShown(bool bCompletionPercentageShown) { m_bCompletionPercentageShown = bCompletionPercentageShown; }
	bool									isCompletionPercentageShown(void) { return m_bCompletionPercentageShown; }

	uint32									getProgressFillColour(void) { return getStyles()->getStyle<uint32>("progress-bar-fill-colour"); }	// RGBA

	void									reset(void);

private:
	float32									m_fProgress;
	uint32									m_uiMax;
	uint8									m_bCompletionPercentageShown	: 1;
};

#endif