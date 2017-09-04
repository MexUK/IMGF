#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include <string>

class bxgi::DATAnimgrpSection;

class bxgi::DATAnimgrpEntry
{
public:
	DATAnimgrpEntry(void);
	
	void					unload(void) {}

	void					unserialize(void);
	void					serialize(void);
	
	void					setSection(DATAnimgrpSection* pDATAnimgrpSection) { m_pDATAnimgrpSection = pDATAnimgrpSection; }
	DATAnimgrpSection*		getSection(void) { return m_pDATAnimgrpSection; }
	
	void					setAnimationName(std::string strAnimationName) { m_strAnimationName = strAnimationName; }
	std::string&			getAnimationName(void) { return m_strAnimationName; }
	
private:
	DATAnimgrpSection*		m_pDATAnimgrpSection;
	std::string				m_strAnimationName;
};