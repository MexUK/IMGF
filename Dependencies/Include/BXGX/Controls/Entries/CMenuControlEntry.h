#ifndef CMenuControlEntry_H
#define CMenuControlEntry_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include "Control/e2DMirroredOrientation.h"
#include "Pool/CVectorPool.h"

class CMenuControl;
class CMenuControlEntry;

class CMenuControlEntry : public CGUIControlComponent_Text, public bxcf::CVectorPool<CMenuControlEntry*>
{
public:
	CMenuControlEntry(void);
	
	void									unload(void) {}

	void									setMenu(CMenuControl *pMenu);
	CMenuControl*							getMenu(void) { return m_pMenu; }

	void									setWindowControlOrientation(e2DMirroredOrientation eOrientation) { m_eOrientation = eOrientation; }
	e2DMirroredOrientation					getWindowControlOrientation(void) { return m_eOrientation; }

	void									setItemId(uint32 uiItemId) { m_uiItemId = uiItemId; }
	uint32									getItemId(void) { return m_uiItemId; }
	
private:
	e2DMirroredOrientation					m_eOrientation;
	uint32									m_uiItemId;
	CMenuControl*							m_pMenu;
};

#endif