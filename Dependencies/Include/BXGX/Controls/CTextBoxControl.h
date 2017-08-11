#ifndef CTextBoxControl_H
#define CTextBoxControl_H

#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Type/Vector/Vec2i.h"
#include "Control/CGUIControl.h"
#include "Styles/CGUIStyles.h"
#include "Control/CGUIScrollPool.h"
#include "Controls/CScrollControl.h"
#include <string>
#include <vector>

class CTextBoxControl : public CGUIControl
{
public:
	CTextBoxControl(void);
	~CTextBoxControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onKeyDown(uint8 uiCharCode);
	bool									onCharDown(uint8 uiCharCode);
	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPoint);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPoint);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPoint);
	void									onRender(void);
	
	bxcf::Vec2i							getCaretRenderStartPosition(void);	// in pixels
	bxcf::Vec2i							getCaretRenderEndPosition(void);	// in pixels

	bool									isCaretAtFarLeft(void);
	bool									isCaretAtFarRight(void);
	bool									isCaretAtFarTop(void);
	bool									isCaretAtFarBottom(void);

	void									setCaretPosition(bxcf::Vec2u& vecCaretPosition);																// parameter is character x,y position
	void									setCaretPositionStart(bxcf::Vec2u& vecCaretPositionStart) { m_vecCaretPositionStart = vecCaretPositionStart; }	// parameter is character x,y position
	void									setCaretPositionEnd(bxcf::Vec2u& vecCaretPositionEnd) { m_vecCaretPositionEnd = vecCaretPositionEnd; }			// parameter is character x,y position
	void									setCaretPositionX(uint32 uiCharacterPositionX);																	// parameter is character x position
	void									setCaretPositionY(uint32 uiCharacterPositionY);																	// parameter is character y position
	void									setCaretPositionStartX(uint32 uiCaretPositionStartX) { m_vecCaretPositionStart.x = uiCaretPositionStartX; }	// parameter is character x position
	void									setCaretPositionStartY(uint32 uiCaretPositionStartY) { m_vecCaretPositionStart.y = uiCaretPositionStartY; }	// parameter is character y position
	void									setCaretPositionEndX(uint32 uiCaretPositionEndX) { m_vecCaretPositionEnd.x = uiCaretPositionEndX; }			// parameter is character x position
	void									setCaretPositionEndY(uint32 uiCaretPositionEndY) { m_vecCaretPositionEnd.y = uiCaretPositionEndY; }			// parameter is character y position
	bxcf::Vec2u&						getCaretPosition(void) { return m_vecCaretPositionStart; }														// return    is character x,y position
	bxcf::Vec2u&						getCaretPositionStart(void) { return m_vecCaretPositionStart; }													// return    is character x,y position
	bxcf::Vec2u&						getCaretPositionEnd(void) { return m_vecCaretPositionEnd; }														// return    is character x,y position
	uint32									getCaretPositionStartX(void) { return m_vecCaretPositionStart.x; }											// return    is character x position
	uint32									getCaretPositionStartY(void) { return m_vecCaretPositionStart.y; }											// return    is character y position
	uint32									getCaretPositionEndX(void) { return m_vecCaretPositionEnd.x; }												// return    is character x position
	uint32									getCaretPositionEndY(void) { return m_vecCaretPositionEnd.y; }												// return    is character y position

	void									moveCaret(bxcf::Vec2i& vecCharacterPositionIncrease);						// parameter is character position offset
	void									moveCaretX(int32 iCaretMoveX) { moveCaret(bxcf::Vec2i(iCaretMoveX, 0)); }	// parameter is character x position offset
	void									moveCaretY(int32 iCaretMoveY) { moveCaret(bxcf::Vec2i(0, iCaretMoveY)); }	// parameter is character x position offset
	void									moveCaretLeft(uint32 uiCharacterPositionIncrease);								// parameter is character x position offset
	void									moveCaretRight(uint32 uiCharacterPositionIncrease);								// parameter is character x position offset

	bool									isTextSelected(void);
	void									selectAllText(void);
	std::string								getSelectedText(void);

	std::string								getTextRange(bxcf::Vec2u& vecRangeStart, bxcf::Vec2u& vecRangeEnd); // range inclusive
	std::string								getLineTextCharacters(bxcf::Vec2u& vecRangeStart, uint32 uiLineCharacterEnd);

	void									addTextAtCaret(std::string& strData);
	void									addTextAtRange(std::string& strData, bxcf::Vec2u& vecRangeStart, bxcf::Vec2u& vecRangeEnd);
	void									addLineText(bxcf::Vec2u& vecCharacterPosition, std::string& strData);

	void									copySelectedText(void);
	void									cutSelectedText(void);
	void									pasteText(void);

	bxcf::Vec2i							getTextLinePosition(uint32 uiLineIndex);	// in pixels
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
	void									splitLine(bxcf::Vec2u& vecCharacterPosition);	// parameter is character position

	void									addCharacter(uint32 uiCharCode);
	void									removeCharacterToLeft(void);
	void									removeCharacterToRight(void);
	void									removeCharacter(bxcf::Vec2u& vecCharacterPosition);	// parameter is character position

	void									removeSelectedText(void);
	void									removeTextRange(bxcf::Vec2u& vecRangeStart, bxcf::Vec2u& vecRangeEnd);	// range inclusive
	void									removeLineTextCharacters(bxcf::Vec2u& vecRangeStart, uint32 uiLineCharacterEnd);

	uint32									getLineMaxCharacterIndex(uint32 uiLineIndex);

private:
	uint8									m_bMultiLine				: 1;
	uint8									m_bHasHorizontalScrollBar	: 1;
	uint8									m_bHasVerticalScrollBar		: 1;
	uint8									m_bReadOnly					: 1;
	bxcf::Vec2u						m_vecCaretPositionStart;				// character position
	bxcf::Vec2u						m_vecCaretPositionEnd;					// character position
	std::vector<std::string>				m_vecTextLines;
};

#endif