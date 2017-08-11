#ifndef CThemeDesignerTab_Save_H
#define CThemeDesignerTab_Save_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
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