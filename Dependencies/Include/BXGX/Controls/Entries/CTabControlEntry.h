#ifndef CTabControlEntry_H
#define CTabControlEntry_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include "Styles/CGUIStyleableEntity.h"
#include <string>
#include <vector>

class CTabControl;

class CTabControlEntry : public CGUIControlComponent_Text, public CGUIStyleableEntity
{
public:
	CTabControlEntry(void);
	
	void									unload(void) {}

	void									setActiveTab(void);
	bool									isActiveTab(void);

	void									setTabControl(CTabControl *pTabControl) { m_pTabControl = pTabControl; }
	CTabControl*							getTabControl(void) { return m_pTabControl; }

	void									setStyleGroups(std::vector<std::string>& vecStyleGroups) { m_vecStyleGroups = vecStyleGroups; }
	std::vector<std::string>&				getStyleGroups(void) { return m_vecStyleGroups; }

private:
	CTabControl*							m_pTabControl;
	std::vector<std::string>				m_vecStyleGroups;
};

#endif