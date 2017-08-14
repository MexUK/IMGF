#ifndef CScrollControl_H
#define CScrollControl_H

#include "Type/Types.h"
#include "Type/Vector/Vec2u.h"
#include "Control/CGUIControl.h"
#include "Styles/CGUIStyles.h"
#include "Control/e2DMirroredOrientation.h"

class CGUIControl;

class CScrollControl : public CGUIControl
{
public:
	CScrollControl(void);
	CScrollControl(e2DMirroredOrientation eOrientation);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bxcf::Vec2i								getBoundingRectanglePosition(void);
	bxcf::Vec2u								getBoundingRectangleSize(void);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseEnter(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseExit(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);

	bool									isPointInSeekBar(bxcf::Vec2i& vecPoint);
	uint32									getSeekBarPositionOffset(void);

	float32									getProgressFor1px(void);						// returns 0.0 to 1.0
	void									increaseProgress(float32 fProgressIncrease);	// parameter 0.0 to 1.0
	float32									getProgressIncreaseForLength(int32 uiLength);	// parameter in pixels, return 0.0 to 1.0

	uint32									getAvailableScrollLength(void);					// returns in pixels

	void									setControl(CGUIControl* pControl) { m_pControl = pControl; }
	CGUIControl*							getControl(void) { return m_pControl; }

	void									setScrollOrientation(e2DMirroredOrientation eScrollOrientation) { m_eScrollOrientation = eScrollOrientation; }
	e2DMirroredOrientation					getScrollOrientation(void) { return m_eScrollOrientation; }

	void									setSeekBarLength(uint32 uiSeekBarLength) { m_uiSeekBarLength = uiSeekBarLength; }	// in pixels
	uint32									getSeekBarLength(void) { return m_uiSeekBarLength; }								// in pixels

	uint32									getSeekBarFillColour(void) { return getStyles()->getStyle<uint32>("fill-colour"); }	// RGBA
	uint32									getSeekBarLineColour(void) { return getStyles()->getStyle<uint32>("border-colour"); }		// RGBA
	
	void									setProgress(float32 fProgress) { m_fProgress = fProgress; }		// 0.0 to 1.0
	float32									getProgress(void) { return m_fProgress; }						// 0.0 to 1.0

	void									setSeekBarMoving(bool bSeekBarIsMoving) { m_bSeekBarIsMoving = bSeekBarIsMoving; }
	bool									isSeekBarMoving(void) { return m_bSeekBarIsMoving; }

	bxcf::Vec2i								getBackgroundBarPosition(void);
	bxcf::Vec2u								getBackgroundBarSize(void);

	bxcf::Vec2i								getSeekBarPosition(void);
	bxcf::Vec2u								getSeekBarSize(void);

private:
	CGUIControl*							m_pControl;
	uint32									m_uiSeekBarLength;
	uint32									m_uiSeekBarFillColour;	// RGBA
	uint32									m_uiSeekBarLineColour;	// RGBA
	float32									m_fProgress;			// 0.0 to 1.0
	e2DMirroredOrientation					m_eScrollOrientation;
	uint8									m_bSeekBarIsMoving		: 1;
};

#endif