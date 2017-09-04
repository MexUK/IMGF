#pragma once

#include "nsbxgx.h"
#include "Shape/Geometry/EGeometry.h"
#include "Shape/EShape.h"
#include "Item/CLayerItem.h"
#include "Renderable/ERenderable.h"

class bxgx::CLayer;
class bxgx::CWindow;

class bxgx::CShape : public CLayerItem
{
public:
	CShape(EGeometry eGeometry, EShape eShapeType);
	virtual ~CShape(void) {}

	void									unload(void) {}

	virtual void							unserialize(bool bSkipShapeId = false);
	virtual void							serialize(void);

	bxgx::item::ERenderable						getItemType(void) { return bxgx::item::SHAPE; }
	uint32									getItemSubType(void) { return m_eShapeType; }

	bool									doesItemHaveFocus(void) { return true; }
	
	void									setGeometry(EGeometry eGeometry) { m_eGeometry = eGeometry; }
	EGeometry						getGeometry(void) { return m_eGeometry; }

	void									setShapeType(EShape eShapeType) { m_eShapeType = eShapeType; }
	EShape								getShapeType(void) { return m_eShapeType; }

	void									setShapeId(uint32 uiShapeId) { m_uiShapeId = uiShapeId; }
	uint32									getShapeId(void) { return m_uiShapeId; }

private:
	EGeometry						m_eGeometry;
	EShape								m_eShapeType;
	uint32									m_uiShapeId;
};