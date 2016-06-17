#ifndef CEditControl_H
#define CEditControl_H

#include "Types.h"
#include "CVector2i32.h"
#include "CPoint2D.h"
#include "GUI/Control/CGUIControl.h"
#include "GUI/Styles/CGUIStyles.h"
#include "GUI/Control/CGUIScrollPool.h"
#include "GUI/Controls/CScrollControl.h"
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
	
	CPoint2D								getCaretRenderStartPosition(void);	// in pixels
	CPoint2D								getCaretRenderEndPosition(void);	// in pixels

	bool									isCaretAtFarLeft(void);
	bool									isCaretAtFarRight(void);
	bool									isCaretAtFarTop(void);
	bool									isCaretAtFarBottom(void);

	void									setCaretPosition(CVector2ui32& vecCaretPosition) { m_vecCaretPosition = vecCaretPosition; }		// parameter is character x,y position
	CVector2ui32&							getCaretPosition(void) { return m_vecCaretPosition; }											// return    is character x,y position
	void									setCaretPositionX(uint32 uiCaretPositionX) { m_vecCaretPosition.m_x = uiCaretPositionX; }		// parameter is character x position
	void									setCaretPositionY(uint32 uiCaretPositionY) { m_vecCaretPosition.m_y = uiCaretPositionY; }		// parameter is character y position
	uint32									getCaretPositionX(void) { return m_vecCaretPosition.m_x; }										// return    is character x position
	uint32									getCaretPositionY(void) { return m_vecCaretPosition.m_y; }										// return    is character y position

	void									moveCaret(CVector2i32& vecCharacterPositionIncrease);						// parameter is character position offset
	void									moveCaretX(int32 iCaretMoveX) { moveCaret(CVector2i32(iCaretMoveX, 0)); }	// parameter is character x position offset
	void									moveCaretY(int32 iCaretMoveY) { moveCaret(CVector2i32(0, iCaretMoveY)); }	// parameter is character x position offset

	CPoint2D								getTextLinePosition(uint32 uiLineIndex);	// in pixels
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

	void									addLine(void);
	void									addLine(uint32 uiLineIndex, std::string& strText);
	void									removeLine(uint32 uiLineIndex);
	void									mergeLines(uint32 uiRowIndex1, uint32 uiRowIndex2);		// parameters are character y positions
	void									splitLine(CVector2ui32& vecCharacterPosition);			// parameter is character position

	void									addCharacter(uint32 uiCharCode);
	void									removeCharacterToLeft(void);
	void									removeCharacterToRight(void);
	void									removeCharacter(CVector2ui32& vecCharacterPosition);	// parameter is character position

private:
	uint8									m_bMultiLine				: 1;
	uint8									m_bHasHorizontalScrollBar	: 1;
	uint8									m_bHasVerticalScrollBar		: 1;
	uint8									m_bReadOnly					: 1;
	CVector2ui32							m_vecCaretPosition;					// character position
	std::vector<std::string>				m_vecTextLines;
};

#endif