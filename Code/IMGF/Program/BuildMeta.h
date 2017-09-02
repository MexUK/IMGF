#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include <string>

class imgf::BuildMeta
{
public:
	BuildMeta(void);

	void						setCurrentVersion(float32 fCurrentVersion) { m_fCurrentVersion = fCurrentVersion; }
	float32						getCurrentVersion(void) { return m_fCurrentVersion; }

	void						setCurrentVersionString(std::string strCurrentVersionString) { m_strCurrentVersionString = strCurrentVersionString; }
	std::string					getCurrentVersionString(void) { return m_strCurrentVersionString; }

	void						setIsAlphaBuild(bool bIsAlphaBuild) { m_bIsAlphaBuild = bIsAlphaBuild; }
	bool						isAlphaBuild(void) { return m_bIsAlphaBuild; }

private:
	float32						m_fCurrentVersion;
	uint8						m_bIsAlphaBuild		: 1;
	std::string					m_strCurrentVersionString;
};