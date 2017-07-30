#ifndef CThemeDesignerTab_H
#define CThemeDesignerTab_H

class CThemeDesigner;

class CThemeDesignerTab
{
public:
	CThemeDesignerTab(CThemeDesigner *pThemeDesigner);

	void							unload(void) {}

	virtual void					bindEvents(void) = 0;
	virtual void					initDesign(void) = 0;

	void							setThemeDesigner(CThemeDesigner* pThemeDesigner) { m_pThemeDesigner = pThemeDesigner; }
	CThemeDesigner*					getThemeDesigner(void) { return m_pThemeDesigner; }

private:
	CThemeDesigner*					m_pThemeDesigner;
};

#endif