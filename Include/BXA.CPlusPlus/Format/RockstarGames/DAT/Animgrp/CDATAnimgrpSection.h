#ifndef CDATAnimgrpSection_H
#define CDATAnimgrpSection_H

#include "BXA.h"
#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "CDATAnimgrpEntry.h"
#include <string>

class bxa::CDATAnimgrpFormat;

class bxa::CDATAnimgrpSection : public bxa::CVectorPool<bxa::CDATAnimgrpEntry*>
{
public:
	CDATAnimgrpSection(void);

	void					unload(void) {}
	
	void					unserialize(void);
	void					serialize(void);
	
	void					setFormat(bxa::CDATAnimgrpFormat* pDATAnimgrpFormat) { m_pDATAnimgrpFormat = pDATAnimgrpFormat; }
	bxa::CDATAnimgrpFormat*		getFormat(void) { return m_pDATAnimgrpFormat; }
	
	void					setWalkStyleName(std::string& strWalkStyleName) { m_strWalkStyleName = strWalkStyleName; }
	std::string&			getWalkStyleName(void) { return m_strWalkStyleName; }
	
	void					setIFPFileName(std::string& strIFPFileName) { m_strIFPFileName = strIFPFileName; }
	std::string&			getIFPFileName(void) { return m_strIFPFileName; }
	
	void					setAnimationType(std::string& strAnimationType) { m_strAnimationType = strAnimationType; }
	std::string&			getAnimationType(void) { return m_strAnimationType; }
	
private:
	bxa::CDATAnimgrpFormat*		m_pDATAnimgrpFormat;
	std::string				m_strWalkStyleName;
	std::string				m_strIFPFileName;
	std::string				m_strAnimationType;
};

#endif