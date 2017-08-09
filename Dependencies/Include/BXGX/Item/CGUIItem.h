#ifndef CGUIItem_H
#define CGUIItem_H

#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Styles/CGUIStyleableEntity.h"
#include "Event/CGUIEventUtilizer.h"
#include <unordered_map>

class CGUILayer;
class CWindow;

class CGUIItem : public CGUIStyleableEntity, public CGUIEventUtilizer
{
public:
	CGUIItem(void);
	virtual ~CGUIItem(void) {}

	void									unload(void) {}

	virtual void							unserialize(bool bSkipItemId = false)	= 0;
	virtual void							serialize(void)							= 0;
	
	virtual bxcf::CPoint2D					getBoundingRectanglePosition(void)						= 0;
	virtual bxcf::CSize2D					getBoundingRectangleSize(void)							= 0;
	virtual void							moveItem(bxcf::CVector2i32& vecItemPositionChange)			= 0;
	virtual void							resizeItemViaOffsets(bxcf::CVector2i32& vecItemSizeChange)	= 0;

	void									onMoveItem(bxcf::CVector2i32& vecItemPositionChange);
	void									onResizeItem(bxcf::CVector2i32& vecItemPositionChange, bxcf::CVector2i32& vecItemSizeChange);

	void									setActiveItem(void);

	CWindow*								getWindow(void);
	void									markToRedraw(void);

	bool									isPointInBoundingRectangle(bxcf::CPoint2D& vecPoint, uint32 uiOuterSpacing);

	void									setLayer(CGUILayer* pLayer) { m_pLayer = pLayer; }
	CGUILayer*								getLayer(void) { return m_pLayer; }

	bool									doesItemHaveFocus(void);

private:
	CGUILayer*								m_pLayer;
	std::unordered_map<uint32, bool>		m_umapEventUsages;
};

#endif