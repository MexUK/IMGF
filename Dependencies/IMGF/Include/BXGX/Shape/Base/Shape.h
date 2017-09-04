#pragma once

#include "nsbxgx.h"
#include "Geometry/Base/EGeometry.h"
#include "Shape/Base/EShape.h"
#include "Item/Layer/LayerItem.h"
#include "Item/Render/ERenderItem.h"

class bxgx::Layer;
class bxgx::Window;

class bxgx::Shape : public LayerItem
{
public:
	Shape(EGeometry eGeometry, EShape eShapeType);
	virtual ~Shape(void) {}

	void									unload(void) {}

	virtual void							unserialize(bool bSkipShapeId = false);
	virtual void							serialize(void);

	bxgx::item::ERenderItem					getItemType(void) { return bxgx::item::SHAPE; }
	uint32									getItemSubType(void) { return m_uiShapeType; }

	bool									doesItemHaveFocus(void) { return true; }
	
	void									setGeometry(EGeometry eGeometry) { m_uiGeometry = eGeometry; }
	EGeometry								getGeometry(void) { return m_uiGeometry; }

	void									setShapeType(EShape eShapeType) { m_uiShapeType = eShapeType; }
	EShape									getShapeType(void) { return m_uiShapeType; }

private:
	EGeometry								m_uiGeometry;
	EShape									m_uiShapeType;
	uint32									m_uiShapeId;
};