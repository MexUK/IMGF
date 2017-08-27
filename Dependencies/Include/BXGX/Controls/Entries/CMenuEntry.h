#pragma once

#include "bxgx.h"
#include "Type/Types.h"
#include "Controls/Components/TextComponent.h"
#include "Control/E2DAxis.h"
#include "Pool/CVectorPool.h"

class bxgx::CMenu;
class bxgx::CMenuEntry;

class bxgx::CMenuEntry : public bxgx::TextComponent, public bxcf::CVectorPool<CMenuEntry*>
{
public:
	CMenuEntry(void);
	
	void									unload(void) {}

	void									setMenu(CMenu *pMenu);
	CMenu*							getMenu(void) { return m_pMenu; }

	void									setWindowControlOrientation(E2DAxis eOrientation) { m_eOrientation = eOrientation; }
	E2DAxis					getWindowControlOrientation(void) { return m_eOrientation; }

	void									setItemId(uint32 uiItemId) { m_uiItemId = uiItemId; }
	uint32									getItemId(void) { return m_uiItemId; }
	
private:
	E2DAxis					m_eOrientation;
	uint32									m_uiItemId;
	CMenu*							m_pMenu;
};