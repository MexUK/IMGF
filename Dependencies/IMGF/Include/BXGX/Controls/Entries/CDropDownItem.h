#pragma once

#include "bxgx.h"
#include "Type/Types.h"
#include "Controls/Components/TextComponent.h"

class bxgx::CDropDown;

class bxgx::CDropDownItem : public bxgx::TextComponent
{
public:
	CDropDownItem(void);

	void									unload(void) {}

	void									setDropControl(CDropDown *pDropControl);
	CDropDown*							getDropControl(void) { return m_pDropControl; }

	void									setIsSelectable(bool bIsSelectable) { m_bIsSelectable = bIsSelectable; }
	bool									isSelectable(void) { return m_bIsSelectable; }

	void									setUserdata(uint32 uiUserdata) { m_uiUserdata = uiUserdata; }
	uint32									getUserdata(void) { return m_uiUserdata; }

	void									setUserdata2(uint32 uiUserdata2) { m_uiUserdata2 = uiUserdata2; }
	uint32									getUserdata2(void) { return m_uiUserdata2; }

private:
	CDropDown*							m_pDropControl;
	bool									m_bIsSelectable;
	uint32									m_uiUserdata;
	uint32									m_uiUserdata2;
};