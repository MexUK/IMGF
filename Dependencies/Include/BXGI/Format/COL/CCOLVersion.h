#ifndef CCOLVersion_H
#define CCOLVersion_H

#include "bxgi.h"
#include "eCOLVersion.h"
#include <string>

class bxgi::CCOLVersion
{
public:
	void				unload(void) {}

	void				setVersionId(bxgi::eCOLVersion eVersionId) { m_eVersionId = eVersionId; }
	bxgi::eCOLVersion			getVersionId(void) { return m_eVersionId; }

	void				setText(std::string strText) { m_strText = strText; }
	std::string			getText(void) { return m_strText; }

	void				setLocalizationKey(std::string strLocalizationKey) { m_strLocalizationKey = strLocalizationKey; }
	std::string			getLocalizationKey(void) { return m_strLocalizationKey; }

private:
	bxgi::eCOLVersion			m_eVersionId;
	std::string			m_strText;
	std::string			m_strLocalizationKey;
};

#endif