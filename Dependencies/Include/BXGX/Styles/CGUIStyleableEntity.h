#ifndef CGUIStyleableEntity_H
#define CGUIStyleableEntity_H

#include "Type/Types.h"
#include "Pool/CMultipleTypeValuesUMapContainer.h"
#include <string>

class CGUIStyles;

class CGUIStyleableEntity
{
public:
	CGUIStyleableEntity(void);
	~CGUIStyleableEntity(void);

	void									setStyles(CGUIStyles *pStyles);
	CGUIStyles*								getStyles(void);

private:
	CGUIStyles*								m_pStyles;
};

#endif