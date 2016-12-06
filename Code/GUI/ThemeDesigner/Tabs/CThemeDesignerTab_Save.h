#ifndef CThemeDesignerTab_Save_H
#define CThemeDesignerTab_Save_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Control/eGUIControl.h"
#include "GUI/ThemeDesigner/Tab/CThemeDesignerTab.h"

class CButtonControl;

class CThemeDesignerTab_Save : public CThemeDesignerTab
{
public:
	CThemeDesignerTab_Save(CThemeDesigner *pThemeDesigner);

	void													bindEvents(void);
	void													initDesign(void);

	void													onPressButton(CButtonControl *pButton);
};

#endif