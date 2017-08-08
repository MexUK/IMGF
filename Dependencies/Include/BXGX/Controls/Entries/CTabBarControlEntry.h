#ifndef CTabBarControlEntry_H
#define CTabBarControlEntry_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include "Styles/CGUIStyleableEntity.h"
#include <string>
#include <vector>

class CTabBarControl;

class CTabBarControlEntry : public CGUIControlComponent_Text, public CGUIStyleableEntity
{
public:
	CTabBarControlEntry(void);
	
	void									unload(void) {}

	void									setActiveTab(void);
	bool									isActiveTab(void);

	void									setTabControl(CTabBarControl *pTabControl) { m_pTabControl = pTabControl; }
	CTabBarControl*							getTabControl(void) { return m_pTabControl; }

	void									setStyleGroups(std::vector<std::string>& vecStyleGroups);
	void									setStyleGroups(std::vector<uint32>& vecStyleGroups) { m_vecStyleGroups = vecStyleGroups; }
	std::vector<uint32>&					getStyleGroups(void) { return m_vecStyleGroups; }

private:
	CTabBarControl*							m_pTabControl;
	std::vector<uint32>						m_vecStyleGroups;
};

#endif