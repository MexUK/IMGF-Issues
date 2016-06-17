#include "CListControl.h"
#include "GUI/Window/CWindow.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "GUI/CGUIManager.h"
#include "GUI/GraphicsLibrary/CGraphicsLibrary.h"
#include "GUI/Controls/CScrollControl.h"
#include "Data Stream/CDataReader.h"
#include "Data Stream/CDataWriter.h"

using namespace std;

auto pOnMouseDown_List		= [](void *pControl, void *pTriggerArg) { ((CListControl*) pControl)->onMouseDown(*(CPoint2D*) pTriggerArg); };
auto pOnRender_List			= [](void *pControl) { ((CListControl*) pControl)->render(); };

CListControl::CListControl(void) :
	CGUIControl(GUI_CONTROL_LIST),
	m_uiRowHeight(50),
	m_uiColumnWidth(100),
	m_uiRowTextHeight(10),
	m_bHasVerticalScrollBar(true)
{
	addScroll(new CScrollControl(_2D_MIRRORED_ORIENTATION_HORIZONTAL));
	addScroll(new CScrollControl(_2D_MIRRORED_ORIENTATION_VERTICAL));
}

// event binding
void					CListControl::bindEvents(void)
{
	storeEventBoundFunction(getWindow()->bindEvent(EVENT_onLeftMouseDown, pOnMouseDown_List, this));
	storeEventBoundFunction(getWindow()->bindEvent(EVENT_onRender, pOnRender_List, this));
}

// serialization
void					CListControl::unserialize(bool bSkipControlId)
{
	CDataReader *pDataReader = CDataReader::getInstance();

	/*
	todo - uncomment when list control is implemented

	CGUIControl::unserialize(bSkipControlId);
	uint32 uiColumnCount = pDataReader->readUint32(); // column count
	for (uint32 i = 0; i < uiColumnCount; i++)
	{
		CListControlHeader *pListColumn = new CListControlHeader;
		pListColumn->setWidth(pDataReader->readUint32()); // column header width
		pListColumn->setText(pDataReader->readStringWithLength()); // column header text
		getHeaders().addEntry(pListColumn);
	}
	uint32 uiRowCount = pDataReader->readUint32(); // row count
	for (CListControlEntry *pListRow : getEntries()) // iterate rows
	{
		uint32 uiTextLineCount = pDataReader->readUint32(); // text line count
		pListRow->getText().resize(uiTextLineCount);
		for (uint32 i = 0; i < uiTextLineCount; i++) // iterate text lines in row
		{
			for (uint32 i2 = 0; i < uiColumnCount; i2++) // iterate cells in text line
			{
				pListRow->getText()[i][i2] = pDataReader->readStringWithLength(); // cell text
			}
		}
	}
	*/
}

void					CListControl::serialize(void)
{
	CDataWriter *pDataWriter = CDataWriter::getInstance();

	/*
	todo - uncomment when list control is implemented

	CGUIControl::serialize();
	pDataWriter->writeUint32(getHeaders().getEntryCount()); // column count
	for (CListControlHeader *pListColumn : getHeaders().getEntries())
	{
		pDataWriter->writeUint32(pListColumn->getWidth()); // column header width
		pDataWriter->writeStringWithLengthRef(pListColumn->getText()); // column header text
	}
	pDataWriter->writeUint32(getHeaders().getEntryCount()); // row count
	for (CListControlEntry *pListRow : getEntries()) // iterate rows
	{
		pDataWriter->writeUint32(pListRow->getText().size()); // text line count
		for (vector<string>& vecText : pListRow->getText()) // iterate text lines in row
		{
			for (string& strCellText : vecText) // iterate cells in text line
			{
				pDataWriter->writeStringWithLengthRef(strCellText); // cell text
			}
		}
	}
	*/
}

// input
void					CListControl::onMouseDown(CPoint2D& vecCursorPosition)
{
	if (isPointInItem(vecCursorPosition))
	{
		CEventManager::getInstance()->setEventHogged(true);
	}
}

// render
void					CListControl::render(void)
{
	CGraphicsLibrary *pGFX = CGUIManager::getInstance()->getGraphicsLibrary();

	if (getStyles()->doesHaveFill())
	{
		pGFX->drawRectangleFill(getPosition(), getSize(), getStyles());
	}

	uint32
		uiRowIndex = 0,
		uiTextRowIndex,
		uiColumnIndex;
	for(auto pListEntry : getEntries())
	{
		pListEntry->checkToRecalculateStringSize(getStyles());

		uint32 uiRowFillColour = (uiRowIndex % 2) == 0 ? getRowFillColour1() : getRowFillColour2(); // todo - used?
		pGFX->drawRectangleFill(getRowPosition(uiRowIndex), getRowSize(), getStyles());

		uiTextRowIndex = 0;
		for(vector<string>& vecText : pListEntry->getText())
		{
			uiColumnIndex = 0;
			for(string& strText : vecText)
			{
				pGFX->drawText(getCellTextPosition(uiRowIndex, uiTextRowIndex, uiColumnIndex), getCellTextSize(uiRowIndex, uiTextRowIndex, uiColumnIndex), strText, getStyles());
				uiColumnIndex++;
			}

			uiTextRowIndex++;
		}
		
		if (uiRowIndex == 10) break; // todo - temp

		uiRowIndex++;
	}

	if (getStyles()->doesHaveBorder())
	{
		pGFX->drawRectangleBorder(getPosition(), getSize(), getStyles());
	}
}

// row
CPoint2D						CListControl::getRowPosition(uint32 uiRowIndex)
{
	return getPosition() + CPoint2D(0, uiRowIndex * getRowHeight());
}

CSize2D							CListControl::getRowSize(void)
{
	return CSize2D(getSize().m_x, getRowHeight());
}

// row text
CPoint2D						CListControl::getCellTextPosition(uint32 uiRowIndex, uint32 uiTextRowIndex, uint32 uiColumnIndex)
{
	return getPosition() + CPoint2D(uiColumnIndex * getColumnWidth(), (uiRowIndex * getRowHeight()) + (uiTextRowIndex * getRowTextHeight()));
}

CSize2D							CListControl::getCellTextSize(uint32 uiRowIndex, uint32 uiTextRowIndex, uint32 uiColumnIndex)
{
	return getSize() + CSize2D(uiColumnIndex * getColumnWidth(), (uiRowIndex * getRowHeight()) + ((uiTextRowIndex + 1) * getRowTextHeight()));
}