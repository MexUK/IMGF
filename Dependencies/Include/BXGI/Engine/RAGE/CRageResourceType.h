#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "ERageResourceType.h"
#include <string>

class bxgi::CRageResourceType
{
public:
	void						unload(void) {}

	std::string					getResourceName(void);
	bxgi::ERageResourceType		getResourceId(void);

	void						setResourceTypeId(bxgi::ERageResourceType eResourceTypeId) { m_eResourceTypeId = eResourceTypeId; }
	bxgi::ERageResourceType		getResourceTypeId(void) { return m_eResourceTypeId; }

	void						setIdentifier(uint32 uiIdentifier) { m_uiIdentifier = uiIdentifier; }
	uint32						getIdentifier(void) { return m_uiIdentifier; }

	void						setName(std::string strName) { m_strName = strName; }
	std::string					getName(void) { return m_strName; }

	void						setFileExtension(std::string strFileExtension) { m_strFileExtension = strFileExtension; }
	std::string					getFileExtension(void) { return m_strFileExtension; }

private:
	bxgi::ERageResourceType		m_eResourceTypeId;
	uint32						m_uiIdentifier;
	std::string					m_strName;
	std::string					m_strFileExtension;
};