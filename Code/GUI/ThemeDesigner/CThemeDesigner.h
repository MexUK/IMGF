#ifndef CThemeDesigner_H
#define CThemeDesigner_H

#include "Type/Vector/CPoint2D.h"
#include "Pool/CVectorPool.h"
#include "GUI/ThemeDesigner/Tab/CThemeDesignerTab.h"
#include <string>
#include <unordered_map>

class CWindow;
class CTabControl;
class CTabControlEntry;
class CGUILayer;
class CRectangleShape;

class CThemeDesigner : public mcore::CVectorPool<CThemeDesignerTab*>
{
public:
	CThemeDesigner(void);

	void									init(void);

	void									bindEvents(void);

	void									initWindow(void);
	void									initWindowDesign(void);
	
	CGUILayer*								addLayer(std::string strLayerKey, bool bLayerIsEnabled = true);

	void									setWindow(CWindow* pWindow) { m_pWindow = pWindow; }
	CWindow*								getWindow(void) { return m_pWindow; }

	void									setTabControl(CTabControl *pTabControl) { m_pTabControl = pTabControl; }
	CTabControl*							getTabControl(void) { return m_pTabControl; }

	void									setItemHoverRectangle(CRectangleShape* pRectangle) { m_pItemHoverRectangle = pRectangle; }
	CRectangleShape*						getItemHoverRectangle(void) { return m_pItemHoverRectangle; }

	void									setActiveItemRectangle(CRectangleShape* pRectangle) { m_pActiveItemRectangle = pRectangle; }
	CRectangleShape*						getActiveItemRectangle(void) { return m_pActiveItemRectangle; }

	void									setThemeDesignerModeEnabled(bool bThemeDesignerModeEnabled);
	bool									isThemeDesignerModeEnabled(void) { return m_bThemeDesignerModeEnabled; }

private:
	uint8													m_bThemeDesignerModeEnabled : 1;
	CWindow*												m_pWindow;
	CTabControl*											m_pTabControl;
	CRectangleShape*										m_pItemHoverRectangle;
	CRectangleShape*										m_pActiveItemRectangle;
	std::unordered_map<std::string, CTabControlEntry*>		m_umapTabControlEntries;
public: // todo
	std::unordered_map<std::string, CGUILayer*>				m_umapTabLayers;
};

#endif