#ifndef CDropControlEntry_H
#define CDropControlEntry_H

#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include <string>

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

private:
	CDropControl*							m_pDropControl;
	bool									m_bIsSelectable;
};

#endif