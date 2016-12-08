#ifndef CGUIItem_H
#define CGUIItem_H

#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Styles/CGUIStyleableEntity.h"

class CGUILayer;
class CWindow;

class CGUIItem : public CGUIStyleableEntity
{
public:
	CGUIItem(void);

	void									unload(void) {}

	virtual void							unserialize(bool bSkipItemId = false)	= 0;
	virtual void							serialize(void)							= 0;

	virtual void							render(void)											= 0;
	virtual bool							isPointInItem(mcore::CPoint2D& vecPoint)						= 0;
	virtual mcore::CPoint2D						getBoundingRectanglePosition(void)						= 0;
	virtual mcore::CSize2D							getBoundingRectangleSize(void)							= 0;
	virtual void							moveItem(mcore::CVector2i32& vecItemPositionChange)			= 0;
	virtual void							resizeItemViaOffsets(mcore::CVector2i32& vecItemSizeChange)	= 0;

	void									onMoveItem(mcore::CVector2i32& vecItemPositionChange);
	void									onResizeItem(mcore::CVector2i32& vecItemPositionChange, mcore::CVector2i32& vecItemSizeChange);

	void									setActiveItem(void);

	CWindow*								getWindow(void);

	bool									isPointInBoundingRectangle(mcore::CPoint2D& vecPoint, uint32 uiOuterSpacing);

	void									setLayer(CGUILayer* pLayer) { m_pLayer = pLayer; }
	CGUILayer*								getLayer(void) { return m_pLayer; }

private:
	CGUILayer*								m_pLayer;
};

#endif