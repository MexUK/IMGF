#ifndef CDATAnimgrpEntry_H
#define CDATAnimgrpEntry_H

#include "bxgi.h"
#include "Type/Types.h"
#include <string>

class bxgi::CDATAnimgrpSection;

class bxgi::CDATAnimgrpEntry
{
public:
	CDATAnimgrpEntry(void);
	
	void					unload(void) {}

	void					unserialize(void);
	void					serialize(void);
	
	void					setSection(CDATAnimgrpSection* pDATAnimgrpSection) { m_pDATAnimgrpSection = pDATAnimgrpSection; }
	CDATAnimgrpSection*		getSection(void) { return m_pDATAnimgrpSection; }
	
	void					setAnimationName(std::string strAnimationName) { m_strAnimationName = strAnimationName; }
	std::string&			getAnimationName(void) { return m_strAnimationName; }
	
private:
	CDATAnimgrpSection*		m_pDATAnimgrpSection;
	std::string				m_strAnimationName;
};

#endif