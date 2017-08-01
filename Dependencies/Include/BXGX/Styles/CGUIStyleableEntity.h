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

	void									setIndividualStyles(CGUIStyles *pStyles);
	CGUIStyles*								getIndividualStyles(void);
	void									resetIndividualStyles(void);

private:
	CGUIStyles*								m_pStyles;
	CGUIStyles*								m_pIndividualStyles;
};

#endif