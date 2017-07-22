#ifndef CEditControl_H
#define CEditControl_H

#include "Type/Types.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CVector2ui32.h"
#include "Type/Vector/CPoint2D.h"
#include "Control/CGUIControl.h"
#include "Styles/CGUIStyles.h"
#include "Control/CGUIScrollPool.h"
#include "Controls/CScrollControl.h"
#include <string>
#include <vector>

class CEditControl : public CGUIControl
{
public:
	CEditControl(void);
	~CEditControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onKeyDown(uint8 uiCharCode);
	void									onCharDown(uint8 uiCharCode);

	void									render(void);
	
	bxa::CPoint2D								getCaretRenderStartPosition(void);	// in pixels
	bxa::CPoint2D								getCaretRenderEndPosition(void);	// in pixels

	bool									isCaretAtFarLeft(void);
	bool									isCaretAtFarRight(void);
	bool									isCaretAtFarTop(void);
	bool									isCaretAtFarBottom(void);

	void									setCaretPosition(bxa::CVector2ui32& vecCaretPosition);																// parameter is character x,y position
	void									setCaretPositionStart(bxa::CVector2ui32& vecCaretPositionStart) { m_vecCaretPositionStart = vecCaretPositionStart; }	// parameter is character x,y position
	void									setCaretPositionEnd(bxa::CVector2ui32& vecCaretPositionEnd) { m_vecCaretPositionEnd = vecCaretPositionEnd; }			// parameter is character x,y position
	void									setCaretPositionX(uint32 uiCharacterPositionX);																	// parameter is character x position
	void									setCaretPositionY(uint32 uiCharacterPositionY);																	// parameter is character y position
	void									setCaretPositionStartX(uint32 uiCaretPositionStartX) { m_vecCaretPositionStart.m_x = uiCaretPositionStartX; }	// parameter is character x position
	void									setCaretPositionStartY(uint32 uiCaretPositionStartY) { m_vecCaretPositionStart.m_y = uiCaretPositionStartY; }	// parameter is character y position
	void									setCaretPositionEndX(uint32 uiCaretPositionEndX) { m_vecCaretPositionEnd.m_x = uiCaretPositionEndX; }			// parameter is character x position
	void									setCaretPositionEndY(uint32 uiCaretPositionEndY) { m_vecCaretPositionEnd.m_y = uiCaretPositionEndY; }			// parameter is character y position
	bxa::CVector2ui32&							getCaretPosition(void) { return m_vecCaretPositionStart; }														// return    is character x,y position
	bxa::CVector2ui32&							getCaretPositionStart(void) { return m_vecCaretPositionStart; }													// return    is character x,y position
	bxa::CVector2ui32&							getCaretPositionEnd(void) { return m_vecCaretPositionEnd; }														// return    is character x,y position
	uint32									getCaretPositionStartX(void) { return m_vecCaretPositionStart.m_x; }											// return    is character x position
	uint32									getCaretPositionStartY(void) { return m_vecCaretPositionStart.m_y; }											// return    is character y position
	uint32									getCaretPositionEndX(void) { return m_vecCaretPositionEnd.m_x; }												// return    is character x position
	uint32									getCaretPositionEndY(void) { return m_vecCaretPositionEnd.m_y; }												// return    is character y position

	void									moveCaret(bxa::CVector2i32& vecCharacterPositionIncrease);						// parameter is character position offset
	void									moveCaretX(int32 iCaretMoveX) { moveCaret(bxa::CVector2i32(iCaretMoveX, 0)); }	// parameter is character x position offset
	void									moveCaretY(int32 iCaretMoveY) { moveCaret(bxa::CVector2i32(0, iCaretMoveY)); }	// parameter is character x position offset
	void									moveCaretLeft(uint32 uiCharacterPositionIncrease);							// parameter is character x position offset
	void									moveCaretRight(uint32 uiCharacterPositionIncrease);							// parameter is character x position offset

	bool									isTextSelected(void);
	void									selectAllText(void);
	std::string								getSelectedText(void);

	std::string								getTextRange(bxa::CVector2ui32& vecRangeStart, bxa::CVector2ui32& vecRangeEnd); // range inclusive
	std::string								getLineTextCharacters(bxa::CVector2ui32& vecRangeStart, uint32 uiLineCharacterEnd);

	void									addTextAtCaret(std::string& strData);
	void									addTextAtRange(std::string& strData, bxa::CVector2ui32& vecRangeStart, bxa::CVector2ui32& vecRangeEnd);
	void									addLineText(bxa::CVector2ui32& vecCharacterPosition, std::string& strData);

	void									copySelectedText(void);
	void									cutSelectedText(void);
	void									pasteText(void);

	bxa::CPoint2D								getTextLinePosition(uint32 uiLineIndex);	// in pixels
	void									setLineText(uint32 uiLineIndex, std::string& strText);
	std::string&							getLineText(uint32 uiLineIndex);
	void									addTextToLine(uint32 uiLineIndex, std::string& strText);
	std::string								getLinePartialText(uint32 uiLineIndex, uint32 uiCharStartIndex, uint32 uiCharReadLength = std::string::npos);	// parameter uiCharReadLength defaults to return rest of line starting from uiCharStartIndex
	uint32									getLineLength(uint32 uiLineIndex);
	uint32									getLineCount(void);

	void									setMultiLine(bool bMultiLine) { m_bMultiLine = bMultiLine; }	// todo - convert text lines into 1 line
	bool									isMultiLine(void) { return m_bMultiLine; }
	
	void									setHasHorizontalScrollBar(bool bHasHorizontalScrollBar) { m_bHasHorizontalScrollBar = bHasHorizontalScrollBar; }
	bool									doesHaveHorizontalScrollBar(void) { return m_bHasHorizontalScrollBar; }
	
	void									setHasVerticalScrollBar(bool bHasVerticalScrollBar) { m_bHasVerticalScrollBar = bHasVerticalScrollBar; }
	bool									doesHaveVerticalScrollBar(void) { return m_bHasVerticalScrollBar; }
	
	void									setReadOnly(bool bReadOnly) { m_bReadOnly = bReadOnly; }
	bool									isReadOnly(void) { return m_bReadOnly; }

	uint32									getCaretColour(void) { return getStyles()->getStyle<uint32>("caret-colour"); }	// RGBA

	std::vector<std::string>&				getTextLines(void) { return m_vecTextLines; }

private:
	void									processKey(uint32 uiCharCode);
	void									processChar(uint32 uiCharCode);
	void									processMetaCharCombination(uint32 uiCharCode);

	void									addLine(void);
	void									addLine(uint32 uiLineIndex, std::string& strText);
	void									removeLine(uint32 uiLineIndex);
	void									mergeLines(uint32 uiRowIndex1, uint32 uiRowIndex2);		// parameters are character y positions
	void									splitLine(bxa::CVector2ui32& vecCharacterPosition);			// parameter is character position

	void									addCharacter(uint32 uiCharCode);
	void									removeCharacterToLeft(void);
	void									removeCharacterToRight(void);
	void									removeCharacter(bxa::CVector2ui32& vecCharacterPosition);	// parameter is character position

	void									removeSelectedText(void);
	void									removeTextRange(bxa::CVector2ui32& vecRangeStart, bxa::CVector2ui32& vecRangeEnd); // range inclusive
	void									removeLineTextCharacters(bxa::CVector2ui32& vecRangeStart, uint32 uiLineCharacterEnd);

	uint32									getLineMaxCharacterIndex(uint32 uiLineIndex);

private:
	uint8									m_bMultiLine				: 1;
	uint8									m_bHasHorizontalScrollBar	: 1;
	uint8									m_bHasVerticalScrollBar		: 1;
	uint8									m_bReadOnly					: 1;
	bxa::CVector2ui32							m_vecCaretPositionStart;				// character position
	bxa::CVector2ui32							m_vecCaretPositionEnd;					// character position
	std::vector<std::string>				m_vecTextLines;
};

#endif