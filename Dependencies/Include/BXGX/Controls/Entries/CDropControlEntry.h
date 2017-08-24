#ifndef CDropControlEntry_H
#define CDropControlEntry_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"

class CDropControl;

class CDropControlEntry : public CGUIControlComponent_Text
{
public:
	CDropControlEntry(void);

	void									unload(void) {}

	void									setDropControl(CDropControl *pDropControl);
	CDropControl*							getDropControl(void) { return m_pDropControl; }

	void									setIsSelectable(bool bIsSelectable) { m_bIsSelectable = bIsSelectable; }
	bool									isSelectable(void) { return m_bIsSelectable; }

	void									setUserdata(uint32 uiUserdata) { m_uiUserdata = uiUserdata; }
	uint32									getUserdata(void) { return m_uiUserdata; }

	void									setUserdata2(uint32 uiUserdata2) { m_uiUserdata2 = uiUserdata2; }
	uint32									getUserdata2(void) { return m_uiUserdata2; }

private:
	CDropControl*							m_pDropControl;
	bool									m_bIsSelectable;
	uint32									m_uiUserdata;
	uint32									m_uiUserdata2;
};

#endif