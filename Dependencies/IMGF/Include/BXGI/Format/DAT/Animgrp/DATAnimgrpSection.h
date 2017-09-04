#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Pool/VectorPool.h"
#include "DATAnimgrpEntry.h"
#include <string>

class bxgi::DATAnimgrpFormat;

class bxgi::DATAnimgrpSection : public bxcf::VectorPool<bxgi::DATAnimgrpEntry*>
{
public:
	DATAnimgrpSection(void);

	void					unload(void) {}
	
	void					unserialize(void);
	void					serialize(void);
	
	void					setFormat(bxgi::DATAnimgrpFormat* pDATAnimgrpFormat) { m_pDATAnimgrpFormat = pDATAnimgrpFormat; }
	bxgi::DATAnimgrpFormat*		getFormat(void) { return m_pDATAnimgrpFormat; }
	
	void					setWalkStyleName(std::string& strWalkStyleName) { m_strWalkStyleName = strWalkStyleName; }
	std::string&			getWalkStyleName(void) { return m_strWalkStyleName; }
	
	void					setIFPFileName(std::string& strIFPFileName) { m_strIFPFileName = strIFPFileName; }
	std::string&			getIFPFileName(void) { return m_strIFPFileName; }
	
	void					setAnimationType(std::string& strAnimationType) { m_strAnimationType = strAnimationType; }
	std::string&			getAnimationType(void) { return m_strAnimationType; }
	
private:
	bxgi::DATAnimgrpFormat*		m_pDATAnimgrpFormat;
	std::string				m_strWalkStyleName;
	std::string				m_strIFPFileName;
	std::string				m_strAnimationType;
};